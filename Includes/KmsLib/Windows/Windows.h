
// Product / Produit	: KmsBase

/// \author	KMS	-	Martin Dubois, ing.
/// \file	Includes/KmsLib/Windows/Windows.h

#pragma once

namespace KmsLib
{

	namespace Windows
	{

		// Constantes
		/////////////////////////////////////////////////////////////////////

		/// \cond	en
		/// \brief	The name of "edit" command
		/// \endcond
		/// \cond	fr
		/// \brief	Le nom de la command "edit"
		/// \endcond
		extern const char * COMMAND_EDIT;

		/// \cond	en
		/// \brief	The name of "open" command
		/// \endcond
		/// \cond	fr
		/// \brief	Le nom de la command "open"
		/// \endcond
		extern const char * COMMAND_OPEN;

		// Fonctions
		/////////////////////////////////////////////////////////////////////

		/// \cond	en
		/// \brief	Register a file extension
		/// \param	aExt			[in]	The file extension to register
		/// \param	aClassId		[in]	The name of the class used for
		///									the	registration
		/// \param	aCommandName	[in]	See COMMAND_...
		/// \param	aCommand		[in]	The command to execute
		/// \endcond
		/// \cond	fr
		/// \brief	Enregistrer une extension de fichier
		/// \param	aExt			[in]	L'extension de fichier a
		///									enregistrer
		/// \param	aClassId		[in]	Le nom de classe a utiliser pour
		///									l'enregistrement
		/// \param	aCommandName	[in]	Voir COMMAND_...
		/// \param	aCommand		[in]	La commande a executer
		/// \endcond
		/// \exception	Exception	CODE_REGISTRY_ERROR
		extern void Extension_Register(const char * aExt,
			const char * aClassId, const char * aCommandName, const char * aCommand );

		/// \cond	en
		/// \brief	Unregister a file extension
		/// \param	aExt			[in]	The file extension to register
		/// \param	aClassId		[in]	The name of the class used for
		///									the	registration
		/// \param	aCommandName	[in]	See COMMAND_...
		/// \endcond
		/// \cond	fr
		/// \brief	Desenregistrer une extension de fichier
		/// \param	aExt			[in]	L'extension de fichier a
		///									enregistrer
		/// \param	aClassId		[in]	Le nom de classe a utiliser pour
		///									l'enregistrement
		/// \param	aCommandName	[in]	Voir COMMAND_...
		/// \endcond
		/// \exception	Exception	CODE_REGISTRY_ERROR
		extern void Extension_Unregister(const char * aExt,
			const char * aClassId, const char * aCommandName );

	}
}