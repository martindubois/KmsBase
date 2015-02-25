
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib/Windows/DriverHandle.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Windows ============================================================
#include <Windows.h>

#include <SetupAPI.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/Windows/DriverHandle.h>

namespace KmsLib
{

	namespace Windows
	{

		// Public
		/////////////////////////////////////////////////////////////////////

		// Default contructor / Constructeur par defaut
		DriverHandle::DriverHandle()
		{
		}

		// Destructor / Destructeur
		DriverHandle::~DriverHandle()
		{
		}

		// Exception :	KmsLib::Exception	CODE_IO_ERROR
		void DriverHandle::CancelAll()
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			if (!CancelIoEx(mHandle, NULL))
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "CancelIoEx( 0x%08x,  ) failed", reinterpret_cast<unsigned int>(mHandle));

				throw new Exception(Exception::CODE_IO_ERROR, "CancelIoEx( ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast< unsigned int >( mHandle ) );
			}

			// NOT TESTED : Testing need multithread program / Test necessite
			//				un programme multi-thread
		}

		// aLink			: [in]	The symbolic name / Le nom du lien symbolique
		// aDesiredAccess	:		See / Voir GENERIC_...
		//
		// Exception : KmsLib::Exception
		void DriverHandle::Connect(const char * aLink, DWORD aDesiredAccess)
		{
			assert(NULL != aLink			);
			assert(0	!= aDesiredAccess	);

			Create(aLink, aDesiredAccess, 0, OPEN_EXISTING, 0);
		}

		// aInterface		:	Interface GUID / Identifiant unique de l'interface
		// aDesiredAccess	:	See / Voir GENERIC_...
		// aFlags			:	See / Voir CONNECT_FLAG_...
		//
		// Exception :	KmsLib::Exception	CODE_REGISTRY_ERROR
		//									CODE_SETUP_API_ERROR
		void DriverHandle::Connect(const GUID & aInterface, DWORD aDesiredAccess, unsigned int aFlags)
		{
			assert(NULL != (&aInterface)	);
			assert(0	!= aDesiredAccess	);

			HDEVINFO lDevInfo = SetupDiGetClassDevs(&aInterface, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
			if (INVALID_HANDLE_VALUE == lDevInfo)
			{
				// NOT TESTED : Not easy to test / Pas facile a tester
				throw new Exception(Exception::CODE_SETUP_API_ERROR, "SetupDiGetClassDevs( , , ,  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, 0 );
			}

			try
			{
				for ( unsigned int i = 0;; i++ )
				{
					SP_DEVINFO_DATA lDevInfoData;

					memset(&lDevInfoData, 0, sizeof(lDevInfoData));
					lDevInfoData.cbSize = sizeof(lDevInfoData);

					if (!SetupDiEnumDeviceInfo(lDevInfo, i, &lDevInfoData))
					{
						throw new Exception(Exception::CODE_NO_SUCH_DEVICE, "No such device",
							NULL, __FILE__, __FUNCTION__, __LINE__, i);
					}

					if (0 != (aFlags & CONNECT_FLAG_OPEN_DEVICE_KEY))
					{
						mDeviceKey.Open(lDevInfo, &lDevInfoData, DIREG_DEV);
					}

					SP_DEVICE_INTERFACE_DATA lDevIntData;

					memset(&lDevIntData, 0, sizeof(lDevIntData));
					lDevIntData.cbSize = sizeof(lDevIntData);

					if (SetupDiEnumDeviceInterfaces(lDevInfo, &lDevInfoData, &aInterface, 0, &lDevIntData))
					{
						unsigned char						lBuffer[4094];
						SP_DEVICE_INTERFACE_DETAIL_DATA   * lDetail = reinterpret_cast<SP_DEVICE_INTERFACE_DETAIL_DATA *>(lBuffer);
						DWORD								lInfo_byte;

						memset(&lBuffer, 0, sizeof(lBuffer));
						lDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

						if (!SetupDiGetDeviceInterfaceDetail(lDevInfo, &lDevIntData, lDetail, sizeof(lBuffer), &lInfo_byte, NULL))
						{
							// NOT TESTED : Not easy to test / Pas facile a tester
							throw new Exception(Exception::CODE_SETUP_API_ERROR, "SetupDiGetDeviceInterfaceDetail( , , , , ,  ) failed",
								NULL, __FILE__, __FUNCTION__, __LINE__, i);
						}

						Connect(lDetail->DevicePath, aDesiredAccess);

						// TESTED : KmsLib_Test.exe - DriverHandle - Setup A
						break;
					}
				}
			}
			catch (...)
			{
				// Inutile de verifier le resultat de cette fonction car
				// cette fonction indique deja une condition d'erreur.
				SetupDiDestroyDeviceInfoList(lDevInfo);

				throw;
			}

			// TESTED : KmsLib_Test.exe - DriverHandle - Setup A
			if (!SetupDiDestroyDeviceInfoList(lDevInfo))
			{
				// NOT TESTED : Not easy to test / Pas facile a tester
				throw new Exception(Exception::CODE_SETUP_API_ERROR, "SetupDiDestroyDeviceInfoList(  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast< unsigned int >( lDevInfo ) );
			}
		}

		// See the Microsoft documentation about the DeviceIoControl function
		// / Voir la documentation de la fonction DeviceIoControl sur le site
		// de Microsoft.
		//
		// aCode			:
		// aIn				: [in ,opt]
		// aInSize_byte		:
		// aOut				: [out,opt]
		// aOutSize_byte	:
		//
		// Retour :	Size of returned data in bytes / Taille des donnees
		//			retournee en octets.
		//
		// Exception : KmsList::Exception
		unsigned int DriverHandle::Control(unsigned int aCode, const void * aIn, unsigned int aInSize_byte, void * aOut, unsigned int aOutSize_byte)
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			DWORD lInfo_byte;

			if (!DeviceIoControl(mHandle, aCode, const_cast<void *>(aIn), aInSize_byte, aOut, aOutSize_byte, &lInfo_byte, NULL))
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "DeviceIoControl( 0x%08x, 0x%08x, , %u bytes, , %u bytes, ,  ) failed",
					reinterpret_cast<unsigned int>(mHandle), aCode, aInSize_byte, aOutSize_byte);

				throw new Exception(Exception::CODE_IOCTL_ERROR, "DeviceIoControl( , , , , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, aCode);
			}

			// TESTED : KmsLib_Test.exe - DriverHandle - Setup A
			if (aOutSize_byte < lInfo_byte)
			{
				// NOT TESTED : Not easy to test / Pas facile a tester
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "DeviceIoControl returned too much data (Code = 0x%08x, Expected = %u bytes, Returned = %u bytes)",
					aCode, aOutSize_byte, lInfo_byte);

				throw new Exception(Exception::CODE_IOCTL_ERROR, "DeviceIoControl returned too much data",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lInfo_byte);
			}

			return lInfo_byte;
		}

	}

}
