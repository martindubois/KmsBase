
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib_Test/ToolBase.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>
#include <KmsLib/ToolBase.h>
#include <KmsTest.h>

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
	"KmsLib_Test\\ToolBase.txt"	,
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

	bool lRetB;

	KmsLib::ToolBase lTB( COMMANDS );

	lRetB = lTB.ParseArguments(1, ARGUMENTS_C0);
	KMS_TEST_ASSERT(!lRetB);

	try
	{
		lRetB = lTB.ParseArguments(2, ARGUMENTS_C0);
		KMS_TEST_ASSERT(false);
	}
	catch (KmsLib::Exception * eE)
	{
		KMS_TEST_ASSERT(KmsLib::Exception::CODE_USER_ERROR == eE->GetCode());
		KMS_TEST_ERROR_INFO;
		eE->Write(stdout);
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

KMS_TEST_END
