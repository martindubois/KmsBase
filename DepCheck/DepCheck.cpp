
// Author / Auteur		KMS	-	Martin Dubois, ing.
// Product / Produit	KmsBase
// File / Fichier		DepCheck/DepCheck.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Common =============================================================
#include "../Common/Version.h"

// Entry point / Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main(unsigned int aCount, const char ** aVector)
{
	assert(1	<=	aCount	);
	assert(NULL	!=	aVector	);

	printf("KmsBase - DepCheck\n");
	printf("Version " VERSION_STR);
#ifdef _DEBUG
	printf(" (Debug)");
#endif // _DEBUG
	printf("\n");
	printf("Compiled at " __TIME__ " on " __DATE__ "\n");

	printf("\nNeeded DLL are correctly installed\n");

	return 0;
}
