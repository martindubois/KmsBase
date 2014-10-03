
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/Windows/FileHandle.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Windows ============================================================
#include <Windows.h>

// ===== Interface ==========================================================
#include <KmsLib\Exception.h>
#include <KmsLib\Windows\FileHandle.h>
#include <KmsTest.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(FileHandle_Base)

	KmsLib::Windows::FileHandle	lFH0;

	lFH0.Create("KmsLib_Test\\Windows\\FileHandle.cpp", GENERIC_READ, 0, OPEN_EXISTING, 0);

	char			lData[1024];
	unsigned int	lRet;

	lRet = lFH0.Read(lData, 1);
	KMS_TEST_ASSERT(1 == lRet);

	try
	{
		lFH0.Write(lData, 1);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IO_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	HANDLE lHandle = lFH0;
	KMS_TEST_ASSERT(INVALID_HANDLE_VALUE != lHandle);

	lFH0.Create(".gitignore", GENERIC_WRITE, 0, OPEN_EXISTING, 0);

	try
	{
		lFH0.Read(lData, 1);
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
		lFH0.Create("DoNotExist", GENERIC_READ, 0, OPEN_EXISTING, 0);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IO_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

KMS_TEST_END
