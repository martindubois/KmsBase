
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/Windows/DriverHandle.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Windows ============================================================
#include <Windows.h>

#pragma warning ( disable : 4005 )
#include <ntddser.h>

// ===== Interface ==========================================================
#include <KmsLib\Exception.h>
#include <KmsLib\Windows\DriverHandle.h>
#include <KmsTest.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(DriverHandle_Base)

	KmsLib::Windows::DriverHandle	lDH0;

	lDH0.Connect("nul:");

	try
	{
		lDH0.CancelAll();
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IO_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		unsigned int lInfo_byte = lDH0.Control(0, NULL, 0, NULL, 0);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IOCTL_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		static const GUID GUID_ZERO = { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

		lDH0.Connect(GUID_ZERO);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NO_SUCH_DEVICE == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		static const GUID GUID_INTERFACE_KEYBOARD = { 0x884b96c3, 0x56ef, 0x11d1, { 0xbc, 0x8c, 0x00, 0xa0, 0xc9, 0x14, 0x05, 0xdd } };

		lDH0.Connect(GUID_INTERFACE_KEYBOARD);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IO_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

KMS_TEST_END


KMS_TEST_BEGIN(DriverHandle_SetupA)

	KmsLib::Windows::DriverHandle	lDH0;

	lDH0.Connect(GUID_DEVINTERFACE_COMPORT);

	unsigned int lInfo_byte = lDH0.Control( IOCTL_SERIAL_CLEAR_STATS, NULL, 0, NULL, 0);

	KMS_TEST_ASSERT(0 == lInfo_byte);

KMS_TEST_END
