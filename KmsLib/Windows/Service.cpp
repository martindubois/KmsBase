
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
				// TESTED : KmsLib_Test.exe - Service - Setup B

				// The config can have been allocated before deleting the
				// service / Le tampon pour la configuration peut avoir
				// ete allouer avant la destruction du service.
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
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		bool Service::IsEnabled()
		{
			return (SERVICE_AUTO_START == GetStartType());

			// TESTED : KmsLib_Test.exe - Service - Setup B
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

			ConnectIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

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
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		bool Service::IsRunning()
		{
			ConnectAndOpenIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			UpdateStatus();

			return (SERVICE_RUNNING == mStatus.dwCurrentState);
		}

		// Return / Retour :
		//	false	= No delay at start / Pas de delai au demarrage
		//	true	= Delay at start / Delai au demarrage
		//
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		bool Service::GetDelayedAutoStart()
		{
			ConnectAndOpenIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mHandle);

			SERVICE_DELAYED_AUTO_START_INFO lOut;

			DWORD lInfo_byte;

			if (!QueryServiceConfig2(mHandle, SERVICE_CONFIG_DELAYED_AUTO_START_INFO, reinterpret_cast<LPBYTE>(&lOut), sizeof(lOut), &lInfo_byte))
			{
				// NOT TESTED : Not easy to test / Pas facile a tester
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR, "QueryServiceConfig2( , , , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, lInfo_byte);
			}

			assert(sizeof(lOut) == lInfo_byte);

			return (FALSE != lOut.fDelayedAutostart);
		}

		// Return / Retour : See / Voir SERVICE_...
		//
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		unsigned int Service::GetStartType()
		{
			ConnectAndOpenIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			UpdateConfig();

			assert(NULL != mConfig);

			return mConfig->dwStartType;
		}

		// aIn	:
		//	false	:	No delay start / Pas de delay au demarrage
		//	true	:	Delay start / Delay au demarrage
		//
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::SetDelayedAutoStart(bool aIn)
		{
			ConnectAndOpenIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mHandle);

			SERVICE_DELAYED_AUTO_START_INFO lIn;

			lIn.fDelayedAutostart = aIn;

			if (!ChangeServiceConfig2(mHandle, SERVICE_CONFIG_DELAYED_AUTO_START_INFO, &lIn))
			{
				// NOT TESTED : Not easy to test / Pas facile a tester
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR, "ChangeServiceConfig2( , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, aIn);
			}
		}

		// aIn	:	See / Voir SERVICE_
		//
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::SetStartType(unsigned int aIn)
		{
			ConnectAndOpenIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mHandle);

			if (!ChangeServiceConfig(mHandle, SERVICE_NO_CHANGE, aIn, SERVICE_NO_CHANGE, NULL, NULL, NULL, NULL, NULL, NULL, NULL))
			{
				// NOT TESTED : Not easy to test / Pas facile a tester
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR, "ChangeServiceConfig( , , , , , , , , , , ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, aIn);
			}
		}

		// aDisplayName	: [in]	Display name / Nom affiche
		// aBinary		: [in]	Binary name including path / Nom de
		//						l'executable incluant le chemin
		//
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Create(const char * aDisplayName, const char * aBinary)
		{
			assert(NULL != aDisplayName	);
			assert(NULL != aBinary		);

			assert(NULL == mHandle	);
			assert(NULL != mName	);

			ConnectIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mManager);

			mHandle = CreateService(mManager, mName, aDisplayName, SERVICE_ACCESS, SERVICE_WIN32_OWN_PROCESS, SERVICE_DISABLED, SERVICE_ERROR_NORMAL, aBinary, NULL, NULL, NULL, NULL, NULL);
			if (NULL == mHandle)
			{
				// NOT TESTED :

				char lMsg[2048];

				sprintf_s(lMsg, "Cannot create the service %s (%s, %s)", mName, aDisplayName, aBinary);

				throw new KmsLib::Exception(KmsLib::Exception::CODE_SERVICE_MANAGER_ERROR,
					"CreateService( , , , , , , , , , , , ,  ) failed", lMsg, __FILE__, __FUNCTION__, __LINE__, 0);
			}
		}

		// Exception : KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Delete()
		{
			ConnectAndOpenIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mHandle);

			if (IsRunning())
			{
				Stop();
			}

			BOOL lRetB = DeleteService(mHandle);
			if (!lRetB)
			{
				// NOT TESTED :
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"DeleteService(  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
			}

			CloseServiceHandle(mHandle);
			mHandle = NULL;
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Start()
		{
			ConnectAndOpenIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mHandle);

			BOOL lRetB = StartService(mHandle, 0, NULL);
			if (!lRetB)
			{
				// NOT TESTED :
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"Cannot start the service", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
			}

			Wait(SERVICE_START_PENDING, SERVICE_RUNNING);
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Disable()
		{
			SetStartType(SERVICE_DISABLED);

			// TESTED : KmsLib_Test.exe - Service - Setup B
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Enable()
		{
			SetStartType(SERVICE_AUTO_START);

			// TESTED : KmsLib_Test.exe - Service - Setup B
		}

		// Private
		/////////////////////////////////////////////////////////////////////

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::ConnectAndOpenIfNeeded()
		{
			ConnectIfNeeded();

			// TESTED : KmsLib_Test.exe - Service - Setup B

			if (NULL == mHandle)
			{
				Open();
			}

			assert(NULL != mHandle);
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::ConnectIfNeeded()
		{
			// TESTED : KmsLib_Test.exe - Service - Setup B

			if (NULL == mManager)
			{
				Connect();
			}

			assert(NULL != mManager);
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Connect()
		{
			assert(NULL == mManager);

			mManager = OpenSCManager(NULL, NULL, SC_MANAGER_ALL_ACCESS);
			if (NULL == mManager)
			{
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"OpenSCManager( , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
			}

			// TESTED : KmsLib_Test.exe - Service - Setup B
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Control(DWORD aControl)
		{
			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mHandle);

			SERVICE_STATUS lSS;

			if (!ControlService(mHandle, aControl, &lSS))
			{
				// NOT TESTED :

				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
				"The service did not accept the stop request", NULL, __FILE__, __FUNCTION__, __LINE__, lSS.dwCurrentState);
			}
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Open()
		{
			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL == mHandle);
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

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Stop()
		{
			// TESTED : KmsLib_Test.exe - Service - Setup B

			Control(SERVICE_CONTROL_STOP);
			Wait	(SERVICE_STOP_PENDING, SERVICE_STOPPED);
		}

		// aPending :
		// aFinal	:
		//
		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::Wait(DWORD aPending, DWORD aFinal)
		{
			// TESTED : KmsLib_Test.exe - Service - Setup B

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
				// NOT TESTED : Not easy to test / Pas facile a tester
				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"The service did not change state as requested", NULL, __FILE__, __FUNCTION__, __LINE__, mStatus.dwCurrentState);
			}
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::UpdateConfig()
		{
			// TESTED : KmsLib_Test.exe - Service - Setup B

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
					// NOT TESTED : Not easy to test / Pas facile a tester
					delete[] reinterpret_cast<unsigned char *>(mConfig);
				}

				mConfig				= reinterpret_cast< QUERY_SERVICE_CONFIG *>( new unsigned char[lSize_byte] );
				mConfigSize_byte	= lSize_byte;
			}
		}

		// Exception :	KmsLib::Exception	CODE_SERVICE_MANAGER_ERROR
		void Service::UpdateStatus()
		{
			// TESTED : KmsLib_Test.exe - Service - Setup B

			assert(NULL != mHandle);

			DWORD	lSize_byte;

			BOOL lRetB = QueryServiceStatusEx(mHandle, SC_STATUS_PROCESS_INFO, reinterpret_cast<LPBYTE>(&mStatus), sizeof(mStatus), &lSize_byte);
			if (!lRetB)
			{
				// NOT TESTED : Not easy to test / Pas facile a tester

				throw new Exception(Exception::CODE_SERVICE_MANAGER_ERROR,
					"QueryServiceStatusEx( , , , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, lSize_byte);
			}
		}

	}
}
