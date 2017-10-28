
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

// ===== Includes ===========================================================
#include  "../Includes/Banner.h"

// ===== Common =============================================================
#include "../Common/Version.h"

// Entry point / Point d'entree
/////////////////////////////////////////////////////////////////////////////

int main(array<System::String ^> ^ aArgs)
{
	assert(nullptr != aArgs);

    Banner("KmsBase", "DepCheck_Net");

	Console::WriteLine();
    Console::WriteLine(L"Needed DLL are correctly installed");

    return 0;
}
