
// Author / Auteur    KMS - Martin Dubois, ing.
// Product / Produit  KmsBase
// File / Fichier     KmsLib_Test/ToolBase.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== C ==================================================================
#include <stdio.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>
#include <KmsLib/ToolBase.h>
#include <KmsTest.h>

// Constants / Constantes
/////////////////////////////////////////////////////////////////////////////

#define TEST_FOLDER "KmsLib_Test\\Tests"

// Tests
/////////////////////////////////////////////////////////////////////////////

static const char * ARGUMENTS_C0[] =
{
	"KmsLib_Test.exe"	,
	"Command"			,
	"Invalid"			,
};

static const char * ARGUMENTS_C1[] =
{
	"KmsLib_Test.exe",
	"Command",
	"ExecuteScript DoNotExist",
};

static const char * ARGUMENTS_C2[] =
{
	"KmsLib_Test.exe"	,
	"Command"			,
	"A"					,
};

static const char * ARGUMENTS_C3[] =
{
	"KmsLib_Test.exe",
	"Command",
	"Help",
};

static const char * ARGUMENTS_F0[] =
{
	"KmsLib_Test.exe"	,
	"File"				,
	"DoNotExist"		,
};

static const char * ARGUMENTS_F1[] =
{
	"KmsLib_Test.exe"			,
	"File"						,
	TEST_FOLDER "\\ToolBase0.txt"  ,
};

static void A(KmsLib::ToolBase * aThis, const char * aArguments)
{
	assert(NULL != aThis		);
	assert(NULL != aArguments	);
}

static const KmsLib::ToolBase::CommandInfo COMMANDS_A[] =
{
	{ "A", A, "A                             A", NULL },

	{ NULL, NULL, NULL, NULL }
};

static const KmsLib::ToolBase::CommandInfo COMMANDS[] =
{
	{ "A"				, NULL								, "A {...}                       A"							, COMMANDS_A	},
	{ "ExecuteScript"	, KmsLib::ToolBase::ExecuteScript	, "ExecuteScript {FileName}      Execute the named script"	, NULL			},
	{ "Exit"			, KmsLib::ToolBase::Exit			, "Exit {Code}                   Exit returning Code"		, NULL			},

	{ NULL, NULL, NULL, NULL }
};

KMS_TEST_BEGIN(ToolBase_Base)
{
    FILE * lFile;

    errno_t lRetE = fopen_s(&lFile, TEST_FOLDER "\\ToolBase1.txt", "r");
    KMS_TEST_COMPARE(0, lRetE);

    // ===== AskUser - unsigned short =======================================

    unsigned short lValue;

    KmsLib::ToolBase::AskUser(lFile, "Name", 10, 99, 54, &lValue);
    KMS_TEST_COMPARE(54, lValue);

    KmsLib::ToolBase::AskUser(lFile, "Name", 10, 99, 54, &lValue);
    KMS_TEST_COMPARE(60, lValue);

    /*
    try
    {
        KmsLib::ToolBase::AskUser(lFile, "Name", 10, 99, 54, &lValue);
        KMS_TEST_ASSERT(false);
    }
    catch (KmsLib::Exception * eE)
    {
        KMS_TEST_ERROR_INFO;
        eE->Write(stdout);
        KMS_TEST_ASSERT(KmsLib::Exception::CODE_FILE_READ_ERROR == eE->GetCode());
    }
    */

    // ===== AskUser - char * ===============================================

    char lString[32];

    KmsLib::ToolBase::AskUser(lFile, "Name", lString, sizeof(lString));
    KMS_TEST_COMPARE(0, strcmp("Test", lString));

    KmsLib::ToolBase::AskUser(lFile, "Name", lString, sizeof(lString));
    KMS_TEST_COMPARE(0, strcmp("", lString));

    KmsLib::ToolBase::AskUser(lFile, "Name", "Default", lString, sizeof(lString));
    KMS_TEST_COMPARE(0, strcmp("Test", lString));

    KmsLib::ToolBase::AskUser(lFile, "Name", "Default", lString, sizeof(lString));
    KMS_TEST_COMPARE(0, strcmp("Default", lString));

    // ===== AskUser_InputFileName ==========================================
    KmsLib::ToolBase::AskUser_InputFileName(lFile, "Name", lString, sizeof(lString));
    KMS_TEST_COMPARE(0, strcmp(TEST_FOLDER "\\FileA.txt", lString));

    // ===== AskUser_OutputFileName =========================================
    KmsLib::ToolBase::AskUser_OutputFileName(lFile, "Name", "Default", lString, sizeof(lString));
    KMS_TEST_COMPARE(0, strcmp("DoesNotExist", lString));

    int lRetI = fclose(lFile);
    KMS_TEST_COMPARE(0, lRetI);

    // ===== Report =========================================================
    KmsLib::ToolBase::Report(KmsLib::ToolBase::REPORT_FATAL_ERROR);
    KmsLib::ToolBase::Report(KmsLib::ToolBase::REPORT_OK);
    KmsLib::ToolBase::Report(KmsLib::ToolBase::REPORT_WARNING);

    // ===== Report - Exception =============================================

    KmsLib::Exception  lE(KmsLib::Exception::CODE_UNKNOWN, "Test", NULL, __FILE__, __FUNCTION__, __LINE__, 0);

    KmsLib::ToolBase::Report(KmsLib::ToolBase::REPORT_ERROR, &lE);

    // ===== Report - const  char  * ========================================
    // Already tested / Deja teste

    KmsLib::ToolBase lTB(COMMANDS);

    // ===== ParseArguments =================================================

    bool lRetB;

    lRetB = lTB.ParseArguments(1, ARGUMENTS_C0);
    KMS_TEST_ASSERT(!lRetB);

    try
    {
        lRetB = lTB.ParseArguments(2, ARGUMENTS_C0);
        KMS_TEST_ERROR();
    }
    catch (KmsLib::Exception * eE)
    {
        KMS_TEST_ERROR_INFO;
        eE->Write(stdout);
        KMS_TEST_COMPARE(KmsLib::Exception::CODE_INVALID_COMMAND_LINE, eE->GetCode());
    }

    lRetB = lTB.ParseArguments(3, ARGUMENTS_C0);
    KMS_TEST_ASSERT(lRetB);

    lRetB = lTB.ParseArguments(3, ARGUMENTS_C1);
    KMS_TEST_ASSERT(lRetB);

    lRetB = lTB.ParseArguments(3, ARGUMENTS_C2);
    KMS_TEST_ASSERT(lRetB);

    lRetB = lTB.ParseArguments(3, ARGUMENTS_C3);
    KMS_TEST_ASSERT(lRetB);

    lRetB = lTB.ParseArguments(3, ARGUMENTS_F0);
    KMS_TEST_ASSERT(lRetB);

    lRetB = lTB.ParseArguments(3, ARGUMENTS_F1);
    KMS_TEST_ASSERT(lRetB);

    // ===== ParseCommands ==================================================
    lTB.ParseCommands("");

    // ===== ExecuteScript ==================================================
}
KMS_TEST_END_2
