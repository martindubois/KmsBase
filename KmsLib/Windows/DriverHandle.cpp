
// Author / Auteur		KMS -	Martin Dubois, ing.
// Product / Produit	KmsBase
// File / Fichier		KmsLib/Windows/DriverHandle.cpp

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

		DriverHandle::DriverHandle()
		{
		}

		DriverHandle::~DriverHandle()
		{
		}

		void DriverHandle::CancelAll()
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			if (!CancelIoEx(mHandle, NULL))
			{
				throw new Exception(Exception::CODE_IO_CANCEL_ERROR, "CancelIoEx( ,  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, 0 );
			}

			// NOT TESTED   KmsLib.DriverHandle
            //              Cancelling IO / Annuler IO<br>
            //              Testing need multithread program / Test necessite
			//				un programme multi-thread
		}

		void DriverHandle::Connect(const char * aLink, DWORD aDesiredAccess)
		{
			assert(NULL != aLink			);
			assert(0	!= aDesiredAccess	);

			Create(aLink, aDesiredAccess, 0, OPEN_EXISTING, 0);
		}

		void DriverHandle::Connect(const GUID & aInterface, DWORD aDesiredAccess, unsigned int aFlags)
		{
			assert(NULL != (&aInterface)	);
			assert(0	!= aDesiredAccess	);

			HDEVINFO lDevInfo = SetupDiGetClassDevs(&aInterface, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
			if (INVALID_HANDLE_VALUE == lDevInfo)
			{
				// NOT TESTED   KmsLib.DriverHandle.ErrorHandling
                //              SetupDiGetClassDevs fail / SetupDiGetClassDevs echoue<br>
                //              Not easy to test / Pas facile a tester
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
						mDeviceKey.Open(lDevInfo, &lDevInfoData, (0 != (aFlags & CONNECT_FLAG_ADMINISTRATOR)) ? RegistryKey::OPEN_FLAG_ADMINISTRATOR : 0);
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
							// NOT TESTED   KmsLib.DriverHandle.ErrorHandling
                            //              SetupDiGetDeviceInterfaceDetail fail /
                            //              SetupDiGetDeviceInterfaceDetail echoue<br>
                            //              Not easy to test / Pas facile a tester
							throw new Exception(Exception::CODE_SETUP_API_ERROR, "SetupDiGetDeviceInterfaceDetail( , , , , ,  ) failed",
								NULL, __FILE__, __FUNCTION__, __LINE__, i);
						}

						Connect(lDetail->DevicePath, aDesiredAccess);

						// TESTED   KmsLib::DriverHandle
                        //          KmsLib_Test.exe - DriverHandle - Setup A<br>
                        //          Connect to a device / Connect a un
                        //          peripherique
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

			// TESTED   KmsLib.DriverHandle
            //          KmsLib_Test.exe - DriverHandle - Setup A<br>
            //          Connect to a device / Connect a un
            //          peripherique
			if (!SetupDiDestroyDeviceInfoList(lDevInfo))
			{
				// NOT TESTED   KmsLib.DriverHandle.ErrorHandling
                //              SetupDiDestroyDeviceInfoList fail /
                //              SetupDiDestroyDeviceInfoList echoue<br>
                //              Not easy to test / Pas facile a tester
				throw new Exception(Exception::CODE_SETUP_API_ERROR, "SetupDiDestroyDeviceInfoList(  ) failed",
					NULL, __FILE__, __FUNCTION__, __LINE__, 0 );
			}
		}

		unsigned int DriverHandle::Control(unsigned int aCode, const void * aIn, unsigned int aInSize_byte, void * aOut, unsigned int aOutSize_byte)
		{
			assert(INVALID_HANDLE_VALUE != mHandle);

			DWORD lInfo_byte;

			if (!DeviceIoControl(mHandle, aCode, const_cast<void *>(aIn), aInSize_byte, aOut, aOutSize_byte, &lInfo_byte, NULL))
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "DeviceIoControl( , 0x%08x, , %u bytes, , %u bytes, ,  ) failed",
					aCode, aInSize_byte, aOutSize_byte);

				throw new Exception(Exception::CODE_IOCTL_ERROR, "DeviceIoControl( , , , , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, aCode);
			}

			// TESTED   KmsLib.DriverHandle
            //          KmsLib_Test.exe - DriverHandle - Setup A<br>
            //          IOCTL / IOCTL
			if (aOutSize_byte < lInfo_byte)
			{
				// NOT TESTED   KmsLib.DriverHandle.ErrorHandling
                //              The device indicates more data than expected
                //              / Le peripherique a indique plus de donnees
                //              qu'attendues<br>
                //              Not easy to test / Pas facile a tester
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
