
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib_Test/DebugLog.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>
#include <KmsTest.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(Exception_Base)

	KmsLib::Exception * lE = new KmsLib::Exception(KmsLib::Exception::CODE_UNKNOWN, "Unknown", NULL, __FILE__, __FUNCTION__, __LINE__, 0);
	KMS_TEST_ASSERT(KmsLib::Exception::CODE_UNKNOWN	== lE->GetCode		());
	KMS_TEST_ASSERT(0								== lE->GetInfoA		());
	KMS_TEST_ASSERT(0								== lE->GetLastError	());
	KMS_TEST_ASSERT(__LINE__ - 4					== lE->GetLine		());
	KMS_TEST_ASSERT(0 == strcmp(__FILE__		, lE->GetFile		()));
	KMS_TEST_ASSERT(0 == strcmp(__FUNCTION__	, lE->GetFunction	()));
	KMS_TEST_ASSERT(0 == strcmp("Unknown"		, lE->GetMessage	()));

	void * lPrevTranslator = KmsLib::Exception::RegisterTranslator();

	try
	{
		*reinterpret_cast<unsigned int *>(NULL) = 0;

		KMS_TEST_ASSERT(false);
	}
	catch ( KmsLib::Exception * eE )
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_ACCESS_VIOLATION == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	try
	{
		volatile unsigned int lA = 1;
		volatile unsigned int lB = 0;

		lA /= lB;

		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_INTEGER_DIVIDE_BY_ZERO == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}

	KmsLib::Exception::RestoreTranslator(lPrevTranslator);

KMS_TEST_END_2