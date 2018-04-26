
// Author / Auteur    KMS - Martin Dubois, ing.
// Product / Produit  KmsBase
// File / Fichier     TODO_Tool/TODO_Tool.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== KmsBase ============================================================
#include <KmsTool.h>

// ----- KmsLib -------------------------------------------------------------
#include <KmsLib/ToolBase.h>

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// ===== Commandes - Niveau 1 ===============================================

// ===== Commandes - Niveau 2 - TODO ========================================
static void TODO_TODO(KmsLib::ToolBase * aThis, const char * aArg);

// Tables de commandes
/////////////////////////////////////////////////////////////////////////////

static const KmsLib::ToolBase::CommandInfo COMMAND_TODO[] =
{
	{ "TODO", TODO_TODO, "TODO                          TODO", NULL },

	{ NULL, NULL, NULL, NULL }
};

static const KmsLib::ToolBase::CommandInfo COMMAND[] =
{
	{ "ExecuteScript"	, KmsLib::ToolBase::ExecuteScript	, "ExecuteScript {FileName}      Execute the script {FileName}"	, NULL			},
	{ "Exit"			, KmsLib::ToolBase::Exit			, "Exit {Code}                   Exit returning {Code}"			, NULL			},
	{ "TODO"            , NULL								, "TODO ...                      TODO"                          , COMMAND_TODO	},

	{ NULL, NULL, NULL, NULL }
};

// Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main(int aCount, const char ** aVector)
{
    assert(0	<  aCount    );
    assert(NULL != aVector   );
    assert(NULL != aVector[0]);

    KMS_TOOL_BANNER("KmsBase", "TODO_Tool.exe", "TODO", "TODO");

    KmsLib::ToolBase lToolBase(COMMAND);

    if (!lToolBase.ParseArguments(aCount, aVector))
    {
        lToolBase.ParseCommands();
    }
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// ===== Commandes - Niveau 1 ===============================================

// ===== Commandes - Niveau 2 - TODO ========================================

void TODO_TODO(KmsLib::ToolBase * aThis, const char * aArg)
{
	// TODO :
}

