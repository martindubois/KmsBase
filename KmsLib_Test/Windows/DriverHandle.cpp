
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib_Test/Windows/DriverHandle.cpp

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

// Constants / Constantes
/////////////////////////////////////////////////////////////////////////////

static const GUID GUID_INTERFACE_KEYBOARD = { 0x884b96c3, 0x56ef, 0x11d1, { 0xbc, 0x8c, 0x00, 0xa0, 0xc9, 0x14, 0x05, 0xdd } };

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(DriverHandle_Base)

	KmsLib::Windows::DriverHandle	lDH0;

	// Always possible to open the NUL device / Toujours possible d'ouvrir
	// le peripherique NUL.
	lDH0.Connect("nul:", GENERIC_READ | GENERIC_WRITE);

	// Nothing to cancel / Rien a canceller
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

	// Invalid IOCTL / IOCTL invalid
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

	// Invalid interface GUID / Identifiant d'interface invalid
	try
	{
		static const GUID GUID_ZERO = { 0x00000000, 0x0000, 0x0000, { 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 } };

		lDH0.Connect(GUID_ZERO, GENERIC_READ | GENERIC_WRITE, 0);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_NO_SUCH_DEVICE == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	// No permission / Pas de permission
	try
	{
		lDH0.Connect(GUID_INTERFACE_KEYBOARD, GENERIC_READ | GENERIC_WRITE, 0);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IO_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	lDH0.mDeviceKey.Open(HKEY_CURRENT_USER, "SOFTWARE");

	try
	{
		lDH0.Connect(GUID_INTERFACE_KEYBOARD, GENERIC_READ | GENERIC_WRITE, KmsLib::Windows::DriverHandle::CONNECT_FLAG_OPEN_DEVICE_KEY);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IO_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	// No permission on the device registry key / Pas de permission pour le
	// cle de registre du peripherique
	try
	{
		lDH0.Connect(GUID_INTERFACE_KEYBOARD, GENERIC_READ | GENERIC_WRITE, KmsLib::Windows::DriverHandle::CONNECT_FLAG_OPEN_DEVICE_KEY | KmsLib::Windows::DriverHandle::CONNECT_FLAG_ADMINISTRATOR);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

KMS_TEST_END_2


KMS_TEST_BEGIN(DriverHandle_SetupA)

	KmsLib::Windows::DriverHandle	lDH0;

	// Connect to RS232-USB adapted / Connexion a l'adaptateur RS232-USB
	lDH0.Connect(GUID_DEVINTERFACE_COMPORT, GENERIC_READ | GENERIC_WRITE, 0);

	unsigned int lInfo_byte = lDH0.Control( IOCTL_SERIAL_CLEAR_STATS, NULL, 0, NULL, 0);

	KMS_TEST_ASSERT(0 == lInfo_byte);

	// No permission on the device registry key / Pas de permission pour le
	// cle de registre du peripherique
	try
	{
		lDH0.Connect(GUID_DEVINTERFACE_COMPORT, GENERIC_READ | GENERIC_WRITE, KmsLib::Windows::DriverHandle::CONNECT_FLAG_OPEN_DEVICE_KEY);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

KMS_TEST_END_2


KMS_TEST_BEGIN(DriverHandle_SetupC)

	KmsLib::Windows::DriverHandle	lDH0;

	// Connect to RS232-USB adapted / Connexion a l'adaptateur RS232-USB
	lDH0.Connect(GUID_DEVINTERFACE_COMPORT, GENERIC_READ | GENERIC_WRITE, KmsLib::Windows::DriverHandle::CONNECT_FLAG_OPEN_DEVICE_KEY);

KMS_TEST_END_2
