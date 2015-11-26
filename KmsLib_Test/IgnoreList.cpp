
// Author / Auteur		:	KMS	-	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib_Test/IgnoreList.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdlib.h>

// ===== KmsBase ============================================================
#include <KmsLib/Exception.h>
#include <KmsTest.h>

#include <KmsLib/IgnoreList.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(IgnoreList_Base)

	KmsLib::IgnoreList lIL0(NULL);

	KMS_TEST_ASSERT(NULL == lIL0.GetParent());

	try
	{
		lIL0.ReadFromFile(".", NULL, "DoesNotExist.txt");
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_IO_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
	}
	
	lIL0.ReadFromFile(".", NULL, ".gitignore");

	KMS_TEST_ASSERT(!	lIL0.IsFileIgnored("Test.cmd"					));
	KMS_TEST_ASSERT(	lIL0.IsFileIgnored("KmsBase.sdf"				));
	KMS_TEST_ASSERT(	lIL0.IsFileIgnored("Linux_Windows_Test0.txt"	));

	KMS_TEST_ASSERT(!	lIL0.IsFolderIgnored("KmsLib_Test"	));
	KMS_TEST_ASSERT(	lIL0.IsFolderIgnored("Release"		));

	KmsLib::IgnoreList lIL1(&lIL0);

	KMS_TEST_ASSERT((&lIL0) == lIL1.GetParent());

	lIL1.ReadFromFile("." SLASH "KmsLib_Test", "." SLASH "KmsLib_Test", ".gitignore");

	KMS_TEST_ASSERT(!lIL1.IsFileIgnored("IgnoreList.cpp"));

	KMS_TEST_ASSERT(!	lIL1.IsFolderIgnored("." SLASH "KmsLib_Test" SLASH "ForIgnoreListTest"	));
	KMS_TEST_ASSERT(	lIL1.IsFolderIgnored("." SLASH "KmsLib_Test" SLASH "ForIgnoreListTest0"	));

	// TODO
	// KMS_TEST_ASSERT(	lIL1.IsFolderIgnored("." SLASH "KmsLib_Test" SLASH "Release"			));

KMS_TEST_END_2
