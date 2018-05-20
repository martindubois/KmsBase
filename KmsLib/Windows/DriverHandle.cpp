
// Author   KMS - Martin Dubois, ing.
// Product  KmsBase
// File     KmsLib/Windows/DriverHandle.cpp

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

// Static function declarations
/////////////////////////////////////////////////////////////////////////////

static void     DestroyDeviceInfoList   (HDEVINFO aDevInfo);
static void     EnumDeviceInfo          (HDEVINFO aDevInfo, unsigned int aIndex, SP_DEVINFO_DATA * aDevInfoData);
static bool     EnumDeviceInterfaces    (HDEVINFO aDevInfo, SP_DEVINFO_DATA * aDevInfoData, const GUID * aInterface, SP_DEVICE_INTERFACE_DATA * aDevIntData);
static HDEVINFO GetClassDevs            (const GUID * aInterface);
static void     GetDeviceInterfaceDetail(HDEVINFO aDevInfo, SP_DEVICE_INTERFACE_DATA * aDevIntData, SP_DEVICE_INTERFACE_DETAIL_DATA * aDetail, unsigned int aSize_byte);

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

		void DriverHandle::Connect(const GUID & aInterface, unsigned int aIndex, DWORD aDesiredAccess, unsigned int aFlags)
		{
			assert(NULL != (&aInterface)	);
			assert(0	!= aDesiredAccess	);

            HDEVINFO lDevInfo = GetClassDevs(&aInterface);
            assert(INVALID_HANDLE_VALUE != lDevInfo);

			try
			{
                unsigned int lIndex = 0;

				for ( unsigned int i = 0;; i++ )
				{
					SP_DEVINFO_DATA lDevInfoData;

                    EnumDeviceInfo(lDevInfo, i, &lDevInfoData);

					SP_DEVICE_INTERFACE_DATA lDevIntData;

					if (EnumDeviceInterfaces(lDevInfo, &lDevInfoData, &aInterface, &lDevIntData))
					{
                        if (aIndex > lIndex)
                        {
                            lIndex++;
                            continue;
                        }

                        if (0 != (aFlags & CONNECT_FLAG_OPEN_DEVICE_KEY))
                        {
                            mDeviceKey.Open(lDevInfo, &lDevInfoData, (0 != (aFlags & CONNECT_FLAG_ADMINISTRATOR)) ? RegistryKey::OPEN_FLAG_ADMINISTRATOR : 0);
                        }

                        unsigned char						lBuffer[4094];
						SP_DEVICE_INTERFACE_DETAIL_DATA   * lDetail = reinterpret_cast<SP_DEVICE_INTERFACE_DETAIL_DATA *>(lBuffer);

                        GetDeviceInterfaceDetail(lDevInfo, &lDevIntData, lDetail, sizeof(lBuffer));

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
            DestroyDeviceInfoList(lDevInfo);
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

// Static functions
/////////////////////////////////////////////////////////////////////////////

// aDevInfo [D--;RW-]

// NOT TESTED  KmsLib.DriverHandle.ErrorHandling
//             SetupDiDestroyDeviceInfoList fail
void DestroyDeviceInfoList(HDEVINFO aDevInfo)
{
    assert(INVALID_HANDLE_VALUE != aDevInfo);

    if (!SetupDiDestroyDeviceInfoList(aDevInfo))
    {
        throw new KmsLib::Exception(KmsLib::Exception::CODE_SETUP_API_ERROR, "SetupDiDestroyDeviceInfoList(  ) failed",
            NULL, __FILE__, __FUNCTION__, __LINE__, 0);
    }
}

// aDevInfo     [---;RW-]
// aIndex
// aDevInfoData [---;-W-]
void EnumDeviceInfo(HDEVINFO aDevInfo, unsigned int aIndex, SP_DEVINFO_DATA * aDevInfoData)
{
    assert(INVALID_HANDLE_VALUE != aDevInfo    );
    assert(NULL                 != aDevInfoData);

    memset(aDevInfoData, 0, sizeof(SP_DEVINFO_DATA));
    aDevInfoData->cbSize = sizeof(SP_DEVINFO_DATA);

    if (!SetupDiEnumDeviceInfo(aDevInfo, aIndex, aDevInfoData))
    {
        throw new KmsLib::Exception(KmsLib::Exception::CODE_NO_SUCH_DEVICE, "No such device",
            NULL, __FILE__, __FUNCTION__, __LINE__, aIndex);
    }
}

// aDevInfo     [---;RW-]
// aDevInfoData [---;R--]
// aInterface   [---;R--]
// aDevIntData  [---;-W-]
bool EnumDeviceInterfaces(HDEVINFO aDevInfo, SP_DEVINFO_DATA * aDevInfoData, const GUID * aInterface, SP_DEVICE_INTERFACE_DATA * aDevIntData)
{
    assert(INVALID_HANDLE_VALUE != aDevInfo    );
    assert(NULL                 != aDevInfoData);
    assert(NULL                 != aInterface  );
    assert(NULL                 != aDevIntData );

    memset(aDevIntData, 0, sizeof(SP_DEVICE_INTERFACE_DATA));
    aDevIntData->cbSize = sizeof(SP_DEVICE_INTERFACE_DATA);

    return (TRUE == SetupDiEnumDeviceInterfaces(aDevInfo, aDevInfoData, aInterface, 0, aDevIntData));
}

// aInterface [---;R--]

// NOT TESTED  KmsLib.DriverHandle.ErrorHandling
//             SetupDiGetClassDevs fail
HDEVINFO GetClassDevs(const GUID * aInterface)
{
    assert(NULL != (&aInterface));

    HDEVINFO lResult = SetupDiGetClassDevs(aInterface, NULL, NULL, DIGCF_DEVICEINTERFACE | DIGCF_PRESENT);
    if (INVALID_HANDLE_VALUE == lResult)
    {
        throw new KmsLib::Exception(KmsLib::Exception::CODE_SETUP_API_ERROR, "SetupDiGetClassDevs( , , ,  ) failed",
            NULL, __FILE__, __FUNCTION__, __LINE__, 0);
    }

    return lResult;
}

// aDevInfo    [---;RW-]
// aDevIntData [---;R--]
// aDetail     [---;-W-]
// aSize_byte

// NOT TESTED  KmsLib.DriverHandle.ErrorHandling
//             SetupDiGetDeviceInterfaceDetail fail
void GetDeviceInterfaceDetail(HDEVINFO aDevInfo, SP_DEVICE_INTERFACE_DATA * aDevIntData, SP_DEVICE_INTERFACE_DETAIL_DATA * aDetail, unsigned int aSize_byte)
{
    assert(INVALID_HANDLE_VALUE                    != aDevInfo   );
    assert(NULL                                    != aDevIntData);
    assert(NULL                                    != aDetail    );
    assert(sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) <  aSize_byte );

    memset(aDetail, 0, aSize_byte);
    aDetail->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

    DWORD lInfo_byte;

    if (!SetupDiGetDeviceInterfaceDetail(aDevInfo, aDevIntData, aDetail, aSize_byte, &lInfo_byte, NULL))
    {
        throw new KmsLib::Exception(KmsLib::Exception::CODE_SETUP_API_ERROR, "SetupDiGetDeviceInterfaceDetail( , , , , ,  ) failed",
            NULL, __FILE__, __FUNCTION__, __LINE__, aSize_byte);
    }

    assert(sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA) <= lInfo_byte);
    assert(aSize_byte                              >= lInfo_byte);
}
