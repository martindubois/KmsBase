
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	Includes/KmsLib/Dump.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Interface ==========================================================
#include <KmsLib/Dump.h>

namespace KmsLib
{

	// Function
	/////////////////////////////////////////////////////////////////////////

	// aOut			: [in,out]
	// aIn			: [in	 ]
	// aInSize_byte	:
	void Dumb(FILE * aOut, const unsigned char * aIn, unsigned int aInSize_byte)
	{
		assert(NULL !=	aOut			);
		assert(NULL !=	aIn				);
		assert(0	<	aInSize_byte	);

		for (unsigned int i = 0; i < aInSize_byte; i++)
		{
			fprintf(aOut, "%02x", aIn[i]);

			switch (i % 16)
			{
			case 3	:
			case 11	:
				fprintf(aOut, "  ");
				break;

			case 7	: fprintf(aOut, "    "	); break;
			case 15	: fprintf(aOut, "\n"	); break;

			default:
				fprintf(aOut, " ");
			}
		}

		fprintf(aOut, "\n");
	}
}
