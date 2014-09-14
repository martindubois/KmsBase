
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/KmsLibTest.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Interface ==========================================================
#include <KmsTest.h>

// Test
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_GROUP_LIST_BEGIN
KMS_TEST_GROUP_LIST_ENTRY("RegistryKey")
KMS_TEST_GROUP_LIST_END

extern int RegistryKey_Base();

KMS_TEST_LIST_BEGIN
	KMS_TEST_LIST_ENTRY(RegistryKey_Base, "RegistryKey - Base", 0, 0)
KMS_TEST_LIST_END

KMS_TEST_MAIN
