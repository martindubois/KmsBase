
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/KmsLib/DebugLog.h

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

	class DebugLog
	{

	public:

		DebugLog(const char * aFolder, const char * aName);

		~DebugLog();

		operator FILE * ();

		bool	IsEnabled() const;

		void	Log(Exception  * aException	);
		void	Log(const char * aFile, unsigned int aLine, const char * aFunction);
		void	Log(const char * aMessage		);

		void	LogTime();

	private:

		static unsigned int sIndex;

		FILE * mFile;

	};

}
