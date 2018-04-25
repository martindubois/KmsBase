
// Author / Auteur    KMS - Martin Dubois, ing.
// Product / Produit  KmsBase
// File / Fichier     DepCheck/DepCheck.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Includes ===========================================================
#include "../Includes/KmsTool.h"

// ===== Common =============================================================
#include "../Common/Version.h"

// Entry point / Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main(unsigned int aCount, const char ** aVector)
{
    assert(1	<= aCount );
    assert(NULL	!= aVector);

    KMS_TOOL_BANNER("KmsBase", "DepCheck", VERSION_STR, VERSION_TYPE );

    printf("\nNeeded DLL are correctly installed\n");

    return 0;
}
