
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/Windows/RegistryKey.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ++ ===============================================================
#include <exception>

// ===== Interface ==========================================================
#include <KmsLib\Exception.h>
#include <KmsLib\Windows\RegistryKey.h>
#include <KmsTest.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(RegistryKey_Base)

	KmsLib::Windows::RegistryKey lKey0;
	KmsLib::Windows::RegistryKey lKey1;
	KmsLib::Windows::RegistryKey lKey2;

	lKey0.Open	(HKEY_CURRENT_USER, "Software");

	KMS_TEST_ASSERT(!lKey0.DoesSubKeyExist("DoesNotExist"));

	lKey1.Create(lKey0, "KmsLib_Test");

	KMS_TEST_ASSERT(lKey0.DoesSubKeyExist("KmsLib_Test"));

	lKey1.SetDefaultValue	("KmsLib_Test");
	lKey1.SetValue			("KmsLib_Test", 1);

	KMS_TEST_ASSERT(1 == lKey1.GetValue_DWORD("KmsLib_Test"	, 0));
	KMS_TEST_ASSERT(1 == lKey1.GetValue_DWORD("DoNotExist"	, 1));

	try
	{
		lKey0.DoesSubKeyExist("\\NotValid\\");
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		lKey1.GetValue_DWORD(NULL, 0);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	lKey1.SetDefaultValue("");

	try
	{
		lKey1.GetValue_DWORD(NULL, 0);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	lKey1.DeleteValue("KmsLib_Test");

	lKey2.Open	(lKey0, "KmsLib_Test"	);
	lKey2.Open	(lKey0, "KmsLib_Test"	);
	lKey2.Create(lKey0, "KmsLib_Test2"	);

	lKey0.DeleteSubKey("KmsLib_Test"	);
	lKey0.DeleteSubKey("KmsLib_Test2"	);

	try
	{
		lKey2.SetValue("KmsLib_Test", 2);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		lKey2.Create(HKEY_LOCAL_MACHINE, "KmsLib_Test");
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		lKey0.DeleteValue("DoNotExist");
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		lKey0.DeleteSubKey("DoNotExist");
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		lKey2.Open(HKEY_LOCAL_MACHINE, "DoNotExist");
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_REGISTRY_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

KMS_TEST_END
