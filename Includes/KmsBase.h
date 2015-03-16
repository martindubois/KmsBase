
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/KmsBase.h

#pragma once

// Compilation
//////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
	#define _WINDOWS_
#else
	#define _LINUX_
#endif // _WIN32

// Includes
//////////////////////////////////////////////////////////////////////////////

// ===== C ===================================================================
#include <assert.h>

// ===== KmsBase =============================================================

#include <SafeAPI.h>

#ifdef _LINUX_	
	#include <WindowsToLinux.h>
#endif // _LINUX_
