
// Product / Produit	:	KmsBase

/// \author	KMS -	Martin Dubois, ing.
/// \file	Includes/KmsBase.h

#pragma once

// Compilation
//////////////////////////////////////////////////////////////////////////////


#ifdef _WIN32
	#define _KMS_WINDOWS_
#else
    #ifdef __APPLE__
        #define _KMS_OS_X_
    #else
        #define _KMS_LINUX_
    #endif
#endif // _WIN32

// Includes
//////////////////////////////////////////////////////////////////////////////

// ===== C ===================================================================
#include <assert.h>

// ===== KmsBase =============================================================

#include <SafeAPI.h>

#if defined( _KMS_LINUX_ ) || defined( _KMS_OS_X_ )
	#include <WindowsToLinux.h>
#endif // _KMS_LINUX_ || _KMS_OS_X_
