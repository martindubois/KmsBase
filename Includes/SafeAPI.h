
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Ficheir		:	Includes/SafeAPI.h

#pragma once

// Macro
//////////////////////////////////////////////////////////////////////////////

#ifdef _LINUX_
	#define SIZE_INFO(S)
#endif // _LINUX_

#ifdef _WINDOWS_
	#define SIZE_INFO(S)	, (S)
#endif // _WINDOWS_
