
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib/Windows/DriverHandle.cpp

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

		// Constructeur par defaut
		DriverHandle::DriverHandle()
		{
		}

		// Destructeur
		DriverHandle::~DriverHandle()
		{
		}

		// Exception : KmsLib::Exception
		void DriverHandle::CancelAll()
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			if (!CancelIoEx(mHandle, NULL))
			{
				throw new Exception(Exception::CODE_IO_ERROR, "CancelIoEx( ,  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast< unsigned int >( mHandle ) );
			}
		}

		// aLink	: [in]	Le nom du lien symbolique
		//
		// Exception : KmsLib::Exception
		void DriverHandle::Connect(const char * aLink)
		{
			assert(NULL != aLink);

			Create(aLink, GENERIC_READ | GENERIC_WRITE, 0, OPEN_EXISTING, 0);
		}

		// aInterface	:	Identifiant unique de l'interface
		//
		// Exception : KmsLib::Exception
		void DriverHandle::Connect(const GUID & aInterface)
		{
			HDEVINFO lDevInfo = SetupDiGetClassDevs(&aInterface, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
			if (INVALID_HANDLE_VALUE == lDevInfo)
			{
				// NOT TESTED
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
							// NOT TESTED
							throw new Exception(Exception::CODE_SETUP_API_ERROR, "SetupDiGetDeviceInterfaceDetail( , , , , ,  ) failed",
								NULL, __FILE__, __FUNCTION__, __LINE__, i);
						}

						Connect(lDetail->DevicePath);
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

			if (!SetupDiDestroyDeviceInfoList(lDevInfo))
			{
				// NOT TESTED
				throw new Exception(Exception::CODE_SETUP_API_ERROR, "SetupDiDestroyDeviceInfoList(  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, reinterpret_cast< unsigned int >( lDevInfo ) );
			}
		}

		// Voir la documentation de la fonction DeviceIoControl sur le site
		// de Microsoft.
		//
		// aCode			:
		// aIn				: [in ,opt]
		// aInSize_byte		:
		// aOut				: [out,opt]
		// aOutSize_byte	:
		//
		// Retour : Taille des donnees retournee dans aOut en octets.
		//
		// Exception : KmsList::Exception
		unsigned int DriverHandle::Control(unsigned int aCode, const void * aIn, unsigned int aInSize_byte, void * aOut, unsigned int aOutSize_byte)
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			DWORD lInfo_byte;

			if (!DeviceIoControl(mHandle, aCode, const_cast<void *>(aIn), aInSize_byte, aOut, aOutSize_byte, &lInfo_byte, NULL))
			{
				throw new Exception(Exception::CODE_IOCTL_ERROR, "DeviceIoControl( , , , , , , ,  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, aCode);
			}

			if (aOutSize_byte < lInfo_byte)
			{
				// NOT TESTED
				throw new Exception(Exception::CODE_IOCTL_ERROR, "DeviceIoControl( , , , , , , ,  ) returned too much data",
					NULL, __FILE__, __FUNCTION__, __LINE__, lInfo_byte);
			}

			return lInfo_byte;
		}

	}

}
