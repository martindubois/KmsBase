
// Auteur	: KMS -		Martin Dubois, ing.
// Projet	: KmsBase
// Fichier	: Includes/KmsLib/Windows/Windows.h

#pragma once

namespace KmsLib
{

	namespace Windows
	{

		// Constantes
		/////////////////////////////////////////////////////////////////////

		extern const char * COMMAND_EDIT;
		extern const char * COMMAND_OPEN;

		// Fonctions
		/////////////////////////////////////////////////////////////////////

		extern void Extension_Register( const char * aExt,
			const char * aClassId, const char * aCommandName, const char * aCommand );

		extern void Extension_Unregister(const char * aExt,
			const char * aClassId, const char * aCommandName );


	}
}