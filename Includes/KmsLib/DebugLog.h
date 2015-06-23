
// Product / Produit	:	KmsBase

/// \author	KMS -	Martin Dubois, ing.
/// \file	Includes/KmsLib/DebugLog.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// ===== Includes ===========================================================
#include <KmsLib/Exception.h>

namespace KmsLib
{

	// Class / Classe
	/////////////////////////////////////////////////////////////////////////

	/// \cond	en
	/// \brief	This class provide debug log functionnality.
	/// \endcond
	/// \cond	fr
	/// \brief	Cette classe fournis une fonctionnalite de journal de
	///			debuggage.
	/// \endcond
	class DebugLog
	{

	public:

		/// \cond	en
		/// \brief	Constructor
		/// \param	aFolder	[in]	Name of the folter where to put the log.
		///							If the folder does not exist, the log is
		///							disabled.
		/// \param	aName	[in]	Name of the log. The process identifier
		///							is added to this name.
		/// \endcond
		/// \cond	fr
		/// \brief	Constructeur
		/// \param	aFolder	[in]	Nom du dossier ou placer les journaux. Si
		///							ce dossier n'existe pas, le journal est
		///							desactive.
		/// \param	aName	[in]	Nom du journal, l'identification du
		///							processus est ajouter a celui-ci.
		/// \endcond
		DebugLog(const char * aFolder, const char * aName);

		/// \cond	en
		/// \brief	Destructor
		/// \endcond
		/// \cond	fr
		/// \brief	Destructeur
		/// \endcond
		~DebugLog();

		/// \cond	en
		/// \brief	Cast operator
		/// \endcond
		/// \cond	fr
		/// \brief	Operateur de conversion de type
		/// \endcond
		operator FILE * ();

		/// \cond	en
		/// \brief	Is the log enabled?
		/// \retval	false	The log is disabled
		/// \retval	true	The log is enabled
		/// \endcond
		/// \cond	fr
		/// \brief	Le journal est-il actif?
		/// \retval	false	Le journal est inactif
		/// \retval	true	Le journal est actif
		/// \endcond
		bool	IsEnabled() const;

		/// \cond	en
		/// \brief	Log an KmsLib::Exception
		/// \param	aException	[in]	The exception
		/// \endcond
		/// \cond	fr
		/// \brief	Ajoute les information au sujet d'un KmsLib::Exception au
		///			journal
		/// \param	aException	[in]	L'exception
		/// \endcond
		void	Log(const Exception * aException);

		/// \cond	en
		/// \brief	Log an execution point in the code
		///	\param	aFile		[in]	Source file name
		/// \param	aFunction	[in]	Function name
		/// \param	aLine				Line number
		/// \endcond
		/// \cond	fr
		/// \brief	Ajoute au journal l'information au sujet d'un endroit
		///			dans le code qui est execute
		/// \param	aFile		[in]	Nom du fichier source
		/// \param	aFunction	[in]	Nom de la function
		/// \param	aLine				Numero de la ligne dans le fichier
		///								source
		/// \endcond
		void	Log(const char * aFile, const char * aFunction, unsigned int aLine);

		/// \cond	en
		/// \brief	Log a simple message
		/// \param	aMessage	[in]	The message
		/// \endcond
		/// \cond	fr
		/// \brief	Ajoute un message simple au journal
		/// \param	aMessage	[in]	Le message
		/// \endcond
		void	Log(const char * aMessage);

		/// \cond	en
		/// \brief	Log the execution time
		/// \endcond
		/// \cond	fr
		/// \brief	Ajoute l'heure au journal
		/// \endcond
		void	LogTime();

	private:

		static unsigned int sIndex;

		FILE * mFile;

	};

}
