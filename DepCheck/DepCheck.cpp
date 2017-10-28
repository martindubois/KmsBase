
// Author / Auteur		KMS	-	Martin Dubois, ing.
// Product / Produit	KmsBase
// File / Fichier		DepCheck/DepCheck.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Includes ===========================================================
#include  "../Includes/Banner.h"

// ===== Common =============================================================
#include "../Common/Version.h"

// Entry point / Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main(unsigned int aCount, const char ** aVector)
{
	assert(1	<=	aCount	);
	assert(NULL	!=	aVector	);

    Banner("KmsBase", "DepCheck");

	printf("\nNeeded DLL are correctly installed\n");

	return 0;
}
