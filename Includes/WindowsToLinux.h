
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/WindowsToLinux.h

#pragma once

// Includes
//////////////////////////////////////////////////////////////////////////////

// ===== C ===================================================================
#include <stdlib.h>
#include <unistd.h>

// ===== sys =================================================================
#include <sys/types.h>

// Data types / Types de donnees
//////////////////////////////////////////////////////////////////////////////

typedef int	errno_t;

// Macros
//////////////////////////////////////////////////////////////////////////////

#define __FUNCTION__	""

// ===== _... ================================================================

#define _access		access

#define _getpid()	getpid()

#define _stricmp	strcasecmp
#define _strnicmp	strncasecmp

// ===== ..._s ===============================================================

#define fopen_s(O,F,M)		((NULL==((*(O))=fopen(F,M)))?1:0)

#define localtime_s(O,I)	(NULL==localtime_r((I),(O))?2:0)
			
#define sprintf_s			sprintf
#define sscanf_s			sscanf
#define strcpy_s(D,Si,So)	strcpy(D,So)
