
// Product / Produit	:	KmsBase

/// \author	KMS -	Martin Dubois, ing.
/// \file	Includes/KmsBase.h

#pragma once

// Compilation
//////////////////////////////////////////////////////////////////////////////

#ifdef _WIN32
	#define _KMS_WINDOWS_
#else
	#define _KMS_LINUX_
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
