
// Author / Auteur	:	KMS -	Martin Dubois, ing.
// Project / Projet :	KmsBase
// File / Fichier	:	KmsLib/Windows/Service.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Windows ============================================================
#include <Windows.h>

// ===== Includes ===========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/Windows/Service.h>

// Constants / Constantes
/////////////////////////////////////////////////////////////////////////////

static const DWORD SERVICE_ACCESS = DELETE | SERVICE_INTERROGATE | SERVICE_QUERY_CONFIG | SERVICE_CHANGE_CONFIG | SERVICE_QUERY_STATUS | SERVICE_START | SERVICE_STOP;

namespace KmsLib
{
	namespace Windows
	{

		// Public
		/////////////////////////////////////////////////////////////////////

		// aServiceName	: [in,keep]		Service name / Nom du service
		Service::Service(const char * aServiceName) : mConfig(NULL), mConfigSize_byte(0), mHandle(NULL), mManager(NULL), mName(aServiceName)
		{
			assert(NULL != mName);
		}

		// Destructor / Destructeur
		Service::~Service()
		{
			if (NULL != mManager)
			{
				// The config can have been allocated before deleting the
				// service.
				if (NULL != mConfig)
				{
					assert(sizeof(mConfig) <= mConfigSize_byte);

					delete[] reinterpret_cast<unsigned char *>(mConfig);
					mConfig = NULL;
					mConfigSize_byte = 0;
				}

				if (NULL != mHandle)
				{
					// NOT TESTED
					// TODO : Test
					CloseServiceHandle(mHandle);
					mHandle = NULL;
				}

				CloseServiceHandle(mManager);
				mManager = NULL;
			}

			assert(NULL	== mConfig			);
			assert(0	== mConfigSize_byte	);
			assert(NULL	== mHandle			);
		}

		// Return :
		//	false	=	The service is disabed / Le service est inactif
		//	true	=	The service is enabled / Le service est actif
		//
		// Exception : KmsLib::Exception
		bool Service::IsEnabled()
		{
			if (NULL == mManager)
			{
				Connect();
			}

			if (NULL == mHandle)
			{
				Open();
			}

			UpdateConfig();

			assert(NULL != mConfig);

			return (SERVICE_AUTO_START == mConfig->dwStartType);
		}

		// Return :
		//	false	=	The service is not installed / Le service n'est pas
		//				installe
		//	true	=	The service is installed / Le service est installe
		//
		// Exception : KmsLib::Exception
		bool Service::IsInstalled()
		{
			assert(NULL != mName);

			if (NULL == mManager)
			{
				Connect();
			}

			assert(NULL != mManager);

			if (NULL == mHandle)
			{
				mHandle = OpenService(mManager, mName, SERVICE_ACCESS);
			}

			return (NULL != mHandle);
		}

		// Return :
		//	false	=	The service is not running / Le service n'est pas
		//				en cours d'execution
		//	true	=	The service is running / Le service est en cours
		//				d'execution
		//
		// Exception : KmsLib::Exception
		bool Service::IsRunning()
		{
			if (NULL == mManager)
			{
				Connect();
			}

			if (NULL == mHandle)
			{
				Open();
			}

			UpdateStatus();

			return (SERVICE_RUNNING == mStatus.dwCurrentState);
		}

		// aDisplayName	: [in]	Display name / Nom affiche
		// aBinary		: [in]	Binary name including path / Nom de
		//						l'executable incluant le chemin
		//
		// Exception :	KmsLib::Exception
		void Service::Create(const char * aDisplayName, const char * aBinary)
		{
			assert(NULL != aDisplayName	);
			assert(NULL != aBinary		);

			assert(NULL == mHandle	);
			assert(NULL != mName	);

			if (NULL == mManager)
			{
				Connect();
			}

			assert(NULL != mManager);

			mHandle = CreateService(mManager, mName, aDisplayName, SERVICE_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DISABLED, SERVICE_ERROR_NORMAL, aBinary, NULL, NULL, NULL, NULL, NULL);
			if (NULL == mHandle)
			{
				char lMsg[2048];

				sprintf_s(lMsg, "Cannot create the service %s (%s, %s)", mName, aDisplayName, aBinary);

				throw new KmsLib::Exception(KmsLib::Exception::CODE_SERVICE_MANAGER_ERROR,
					"CreateService( , , , , , , , , , , , ,  ) failed", lMsg, __FILE__, __FUNCTION__, __LINE__, 0);
			}
		}

		// Exception : KmsLib::Exception
		void Service::Delete()
		{
			if (NULL == mManager)
			{
				Connect();
			}

			if (NULL == mHandle)
			{
				Open();
			}

			assert(NULL != mHandle);

			if (IsRunning())
			{
				Stop();
			}

			BOOL lRetB = DeleteService(mHandle);
			if (!lRetB)
			{
				// NOT TESTED :
				// TODO : Test
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"DeleteService(  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
			}

			CloseServiceHandle(mHandle);
			mHandle = NULL;
		}

		// Exception : KmsLib::Exception
		void Service::Start()
		{
			if (NULL == mManager)
			{
				Connect();
			}

			if (NULL == mHandle)
			{
				Open();
			}

			assert(NULL != mHandle);

			BOOL lRetB = StartService(mHandle, 0, NULL);
			if (!lRetB)
			{
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"Cannot start the service", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
			}

			Wait(SERVICE_START_PENDING, SERVICE_RUNNING);
		}

		// Exception : KmsLib::Exception
		void Service::Disable()
		{
			if (NULL == mManager)
			{
				Connect();
			}

			if (NULL == mHandle)
			{
				Open();
			}

			UpdateConfig();

			assert(NULL != mConfig);

			mConfig->dwStartType = SERVICE_DISABLED;

			ApplyConfig();
		}

		// Exception : KmsLib::Exception
		void Service::Enable()
		{
			if (NULL == mManager)
			{
				Connect();
			}

			if (NULL == mHandle)
			{
				Open();
			}

			UpdateConfig();

			assert(NULL != mConfig);

			mConfig->dwStartType = SERVICE_AUTO_START;

			ApplyConfig();
		}

		// Private
		/////////////////////////////////////////////////////////////////////

		// Exception : KmsLib::Exception
		void Service::Connect()
		{
			assert(NULL == mManager);

			mManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
			if (NULL == mManager)
			{
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"OpenSCManager( , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
			}
		}

		// Exception : KmsLib::Exception
		void Service::Control(DWORD aControl)
		{
			assert(NULL != mHandle);

			SERVICE_STATUS lSS;

			if (!ControlService(mHandle, aControl, &lSS))
			{
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
				"The service did not accept the stop request", NULL, __FILE__, __FUNCTION__, __LINE__, lSS.dwCurrentState);
			}
		}

		// Exception : KmsLib::Exception
		void Service::Open()
		{
			assert(NULL == mHandle	);
			assert(NULL != mManager	);
			assert(NULL != mName	);

			mHandle = OpenService(mManager, mName, SERVICE_ACCESS);
			if (NULL == mHandle)
			{
				char lMsg[2048];

				sprintf_s(lMsg, "Cannot open service %s", mName);

				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"OpenSCManager( , ,  ) failed", lMsg, __FILE__, __FUNCTION__, __LINE__, 0);
			}
		}

		// Exception : KmsLib::Exception
		void Service::Stop()
		{
			Control	(SERVICE_CONTROL_STOP);
			Wait	(SERVICE_STOP_PENDING, SERVICE_STOPPED);
		}

		// aPending :
		// aFinal	:
		//
		// Exception : KmsLib::Exception
		void Service::Wait(DWORD aPending, DWORD aFinal)
		{
			for (unsigned int lRetry = 0; lRetry < 30; lRetry++)
			{
				Sleep(500); // 0.5 s

				UpdateStatus();
				if (aPending != mStatus.dwCurrentState)
				{
					break;
				}
			}

			if (aFinal != mStatus.dwCurrentState)
			{
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"The service did not change state as requested", NULL, __FILE__, __FUNCTION__, __LINE__, mStatus.dwCurrentState);
			}
		}

		// Exception : KmsLib::Exception
		void Service::ApplyConfig()
		{
			assert(NULL != mConfig);
			assert(SERVICE_ERROR_NORMAL			== mConfig->dwErrorControl	);
			assert(SERVICE_WIN32_OWN_PROCESS	== mConfig->dwServiceType	);
			assert((SERVICE_AUTO_START == mConfig->dwStartType) || (SERVICE_DISABLED == mConfig->dwStartType));
			assert(NULL != mHandle);

			BOOL lRetB = ChangeServiceConfig(mHandle, mConfig->dwServiceType, mConfig->dwStartType, mConfig->dwErrorControl, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
			if (!lRetB)
			{
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"ChangeServiceConfig( , , , , , , , , , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
			}
		}

		// Exception : KmsLib::Exception
		void Service::UpdateConfig()
		{
			assert(NULL != mHandle);

			DWORD	lSize_byte;

			while (!QueryServiceConfig(mHandle, mConfig, mConfigSize_byte, &lSize_byte))
			{
				if (ERROR_INSUFFICIENT_BUFFER != GetLastError())
				{
					throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
						"QueryServiceConfig( , , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, lSize_byte);
				}

				assert(mConfigSize_byte < lSize_byte);

				if (NULL != mConfig)
				{
					delete[] reinterpret_cast<unsigned char *>(mConfig);
				}

				mConfig				= reinterpret_cast< QUERY_SERVICE_CONFIG *>( new unsigned char[lSize_byte] );
				mConfigSize_byte	= lSize_byte;
			}
		}

		// Exception : KmsLib::Exception
		void Service::UpdateStatus()
		{
			assert(NULL != mHandle);

			DWORD	lSize_byte;

			BOOL lRetB = QueryServiceStatusEx(mHandle, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&mStatus), sizeof(mStatus), &lSize_byte);
			if (!lRetB)
			{
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"QueryServiceStatusEx( , , , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, lSize_byte);
			}
		}

	}
}