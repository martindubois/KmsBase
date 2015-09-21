
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/KmsLibTest.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== Interface ==========================================================
#include <KmsTest.h>

// Test
/////////////////////////////////////////////////////////////////////////////

// Setup A :	The RS232 to USB converter is connected to the computer / Le
//				convertisseur RS232 a USB est connecte a l'ordinateur.
//
// Setup B :	Run as administrator / Execute en tant qu'administrateur.
//
// Setup C :	The RS232 to USB converter is connected to the computer and
//				the test program run as administrator / Le convertisseur
//				RS232 a USB est connecte a l'ordinateur et le programme de
//				test s'execute en tant qu'administrateur.

KMS_TEST_GROUP_LIST_BEGIN
	KMS_TEST_GROUP_LIST_ENTRY("Base"	)
	
	#ifdef _KMS_WINDOWS_
		KMS_TEST_GROUP_LIST_ENTRY("Setup-A" )
		KMS_TEST_GROUP_LIST_ENTRY("Setup-B"	)
		KMS_TEST_GROUP_LIST_ENTRY("Setup-C"	)
	#endif // _KMS_WINDOWS_
KMS_TEST_GROUP_LIST_END

extern int CmdLineParser_Base	();
extern int DebugLog_Base	();
extern int Dump_Base		();
extern int Exception_Base	();
extern int MemTester_Base	();
extern int OpenCL_Base			();
extern int Ring_Base			();
extern int RLE_Base			();
extern int ToolBase_Base	();

#ifdef _KMS_WINDOWS_
	extern int ComPortHandle_Base	();
	extern int ComPortHandle_SetupA	();
	extern int DriverHandle_Base	();
	extern int DriverHandle_SetupA	();
	extern int DriverHandle_SetupC	();
	extern int FileHandle_Base		();
	extern int RegistryKey_Base		();
	extern int Service_Base			();
	extern int Service_SetupB		();
	extern int SystemLog_Base		();
	extern int SystemLog_SetupB		();
#endif // _KMS_WINDOWS_

KMS_TEST_LIST_BEGIN
	KMS_TEST_LIST_ENTRY(CmdLineParser_Base	, "CmdLineParser - Base"	, 0, 0)
	KMS_TEST_LIST_ENTRY(DebugLog_Base	, "DebugLog - Base"		, 0, 0	)
	KMS_TEST_LIST_ENTRY(Dump_Base		, "Dump - Base"			, 0, 0	)
	KMS_TEST_LIST_ENTRY(Exception_Base	, "Exception - Base"	, 0, 0	)
	KMS_TEST_LIST_ENTRY(MemTester_Base	, "MemTester - Base"	, 0, 0	)
	KMS_TEST_LIST_ENTRY(OpenCL_Base			, "OpenCL - Base"			, 0, 0)
	KMS_TEST_LIST_ENTRY(RLE_Base		, "RLE - Base"			, 0, 0	)
	KMS_TEST_LIST_ENTRY(Ring_Base			, "Ring - Base"				, 0, 0)
	KMS_TEST_LIST_ENTRY(ToolBase_Base	, "ToolBase - Base"		, 0, 0	)
	
	#ifdef _KMS_WINDOWS_
		KMS_TEST_LIST_ENTRY(ComPortHandle_Base	, "ComPortHandle - Base"	, 0, 0									)
		KMS_TEST_LIST_ENTRY(ComPortHandle_SetupA, "ComPortHandle - SetupA"	, 1, KMS_TEST_FLAG_INTERACTION_NEEDED	)
		KMS_TEST_LIST_ENTRY(DriverHandle_Base	, "DriverHandle - Base"		, 0, 0									)
		KMS_TEST_LIST_ENTRY(DriverHandle_SetupA	, "DriverHandle - Setup A"	, 1, KMS_TEST_FLAG_INTERACTION_NEEDED	)
		KMS_TEST_LIST_ENTRY(DriverHandle_SetupC	, "DriverHandle - Setup C"	, 3, KMS_TEST_FLAG_INTERACTION_NEEDED	)
		KMS_TEST_LIST_ENTRY(FileHandle_Base		, "FileHandle - Base"		, 0, 0									)
		KMS_TEST_LIST_ENTRY(RegistryKey_Base	, "RegistryKey - Base"		, 0, 0									)
		KMS_TEST_LIST_ENTRY(Service_Base		, "Service - Base"			, 0, 0									)
		KMS_TEST_LIST_ENTRY(Service_SetupB		, "Service - Setup B"		, 2, KMS_TEST_FLAG_INTERACTION_NEEDED	)
		KMS_TEST_LIST_ENTRY(SystemLog_Base		, "SystemLog - Base"		, 0, 0									)
		KMS_TEST_LIST_ENTRY(SystemLog_SetupB	, "SystemLog - SetupB"		, 2, KMS_TEST_FLAG_INTERACTION_NEEDED	)
	#endif // _KMS_WINDOWS_
KMS_TEST_LIST_END

KMS_TEST_MAIN
