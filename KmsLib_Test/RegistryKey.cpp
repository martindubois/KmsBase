
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/RegistryKey.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ++ ===============================================================
#include <exception>

// ===== Interface ==========================================================
#include <KmsLib\Windows\RegistryKey.h>
#include <KmsTest.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(RegistryKey_Base)

	KmsLib::Windows::RegistryKey lKey0;
	KmsLib::Windows::RegistryKey lKey1;
	KmsLib::Windows::RegistryKey lKey2;

	lKey0.Open	(HKEY_CURRENT_USER, "Software");


	lKey1.Create			(lKey0, "KmsLib_Test");
	lKey1.SetDefaultValue	("KmsLib_Test");
	lKey1.SetValue			("KmsLib_Test", 1);
	lKey1.DeleteValue		("KmsLib_Test");

	lKey2.Open	(lKey0, "KmsLib_Test"	);
	lKey2.Open	(lKey0, "KmsLib_Test"	);
	lKey2.Create(lKey0, "KmsLib_Test2"	);

	lKey0.DeleteSubKey("KmsLib_Test"	);
	lKey0.DeleteSubKey("KmsLib_Test2"	);

	try
	{
		lKey2.SetValue("KmsLib_Test", 2);
	}
	catch (std::exception *)
	{
	}

	try
	{
		lKey2.Create(HKEY_LOCAL_MACHINE, "KmsLib_Test");
	}
	catch (std::exception *)
	{
	}

	try
	{
		lKey0.DeleteValue("DoNotExist");
	}
	catch (std::exception *)
	{
	}

	try
	{
		lKey0.DeleteSubKey("DoNotExist");
	}
	catch (std::exception *)
	{
	}

	try
	{
		lKey2.Open(HKEY_LOCAL_MACHINE, "DoNotExist");
	}
	catch (std::exception *)
	{
	}

	KMS_TEST_END
