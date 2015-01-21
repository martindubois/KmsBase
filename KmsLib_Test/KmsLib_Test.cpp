
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/KmsLibTest.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Interface ==========================================================
#include <KmsTest.h>

// Test
/////////////////////////////////////////////////////////////////////////////

// Setup A :	The RS232 to USB converter is connected to the computer / Le
//				convertisseur RS232 a USB est connecte a l'ordinateur.
//
// Setup B :	Run as administrator / Execute en tant qu'administrateur.

KMS_TEST_GROUP_LIST_BEGIN
	KMS_TEST_GROUP_LIST_ENTRY("DriverHandle"	)
	KMS_TEST_GROUP_LIST_ENTRY("FileHandle"		)
	KMS_TEST_GROUP_LIST_ENTRY("RegistryKey"		)
	KMS_TEST_GROUP_LIST_ENTRY("Service"			)
	KMS_TEST_GROUP_LIST_ENTRY("SystemLog"		)
	KMS_TEST_GROUP_LIST_ENTRY("ToolBase"		)
	KMS_TEST_GROUP_LIST_ENTRY("Setup-A"         )
	KMS_TEST_GROUP_LIST_ENTRY("Setup-B"			)
KMS_TEST_GROUP_LIST_END

extern int DriverHandle_Base	();
extern int DriverHandle_SetupA	();
extern int FileHandle_Base		();
extern int RegistryKey_Base		();
extern int Service_Base			();
extern int Service_SetupB		();
extern int SystemLog_Base		();
extern int SystemLog_SetupB		();
extern int ToolBase_Base		();

KMS_TEST_LIST_BEGIN
	KMS_TEST_LIST_ENTRY(DriverHandle_Base	, "DriverHandle - Base"		, 0, 0									)
	KMS_TEST_LIST_ENTRY(DriverHandle_SetupA	, "DriverHandle - Setup A"	, 6, KMS_TEST_FLAG_INTERACTION_NEEDED	)
	KMS_TEST_LIST_ENTRY(FileHandle_Base		, "FileHandle - Base"		, 1, 0									)
	KMS_TEST_LIST_ENTRY(RegistryKey_Base	, "RegistryKey - Base"		, 2, 0									)
	KMS_TEST_LIST_ENTRY(Service_Base		, "Service - Base"			, 3, 0									)
	KMS_TEST_LIST_ENTRY(Service_SetupB		, "Service - Setup B"		, 7, KMS_TEST_FLAG_INTERACTION_NEEDED	)
	KMS_TEST_LIST_ENTRY(SystemLog_Base		, "SystemLog - Base"		, 5, 0									)
	KMS_TEST_LIST_ENTRY(SystemLog_SetupB	, "SystemLog - SetupB"		, 7, KMS_TEST_FLAG_INTERACTION_NEEDED	)
	KMS_TEST_LIST_ENTRY(ToolBase_Base		, "ToolBase - Base"			, 4, 0									)
KMS_TEST_LIST_END

KMS_TEST_MAIN
