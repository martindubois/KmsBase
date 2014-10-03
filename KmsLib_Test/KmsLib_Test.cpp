
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
	KMS_TEST_GROUP_LIST_ENTRY("DriverHandle"	)
	KMS_TEST_GROUP_LIST_ENTRY("FileHandle"		)
	KMS_TEST_GROUP_LIST_ENTRY("RegistryKey"		)
	KMS_TEST_GROUP_LIST_ENTRY("ToolBase"		)
	KMS_TEST_GROUP_LIST_ENTRY("Setup-A"         )
KMS_TEST_GROUP_LIST_END

extern int DriverHandle_Base	();
extern int DriverHandle_SetupA	();
extern int FileHandle_Base		();
extern int RegistryKey_Base		();
extern int ToolBase_Base		();

KMS_TEST_LIST_BEGIN
	KMS_TEST_LIST_ENTRY(DriverHandle_Base	, "DriverHandle - Base"		, 0, 0									)
	KMS_TEST_LIST_ENTRY(DriverHandle_SetupA	, "DriverHandle - Setup A"	, 4, KMS_TEST_FLAG_INTERACTION_NEEDED	)
	KMS_TEST_LIST_ENTRY(FileHandle_Base		, "FileHandle - Base"		, 1, 0									)
	KMS_TEST_LIST_ENTRY(RegistryKey_Base	, "RegistryKey - Base"		, 2, 0									)
	KMS_TEST_LIST_ENTRY(ToolBase_Base		, "ToolBase - Base"			, 3, 0)
	KMS_TEST_LIST_END

KMS_TEST_MAIN
