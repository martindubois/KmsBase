
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/KmsLib/RLE.h

#pragma once

namespace KmsLib
{

	// Functions / Fonctions
	/////////////////////////////////////////////////////////////////////////

	extern unsigned int	RLE_Compress	(const unsigned char * aIn, unsigned int aInSize_byte, unsigned char * aOut, unsigned int aOutSize_byte);
	extern unsigned int	RLE_Uncompress	(const unsigned char * aIn, unsigned int aInSize_byte, unsigned char * aOut, unsigned int aOutSize_byte);

	extern unsigned int	RLE_ComputeCompressedSize	(const unsigned char * aIn, unsigned int aInSize_byte);
	extern unsigned int	RLE_ComputeUncompressedSize	(const unsigned char * aIn, unsigned int aInSize_byte);
}
