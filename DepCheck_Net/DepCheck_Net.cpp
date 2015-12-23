
// Author / Auteur		KMS	-	Martin Dubois, ing.
// Product / Produit	KmsBase
// File / Fichier		DepCheck_Net/DepCheck_Net.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== .Net ===============================================================
using namespace System;

// ===== Common =============================================================
#include "../Common/Version.h"

// Entry point / Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main(array<System::String ^> ^ aArgs)
{
	assert(nullptr != aArgs);

	printf("KmsBase - DepCheck_NET\n");
	printf("Version " VERSION_STR);
#ifdef _DEBUG
	printf(" (Debug)");
#endif // _DEBUG
	printf("\n");
	printf("Compiled at " __TIME__ " on " __DATE__ "\n");

	Console::WriteLine();
    Console::WriteLine(L"Needed DLL are correctly installed");

    return 0;
}
