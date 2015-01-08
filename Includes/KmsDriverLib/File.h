
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	Includes/KmsDriverLib/File.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== KmsDriverLib =======================================================
#include <KmsDriverLib/Object.h>

namespace KmsDriverLib
{

	// Points d'entree
	/////////////////////////////////////////////////////////////////////////

	extern "C"
	{

	}

	// Class
	/////////////////////////////////////////////////////////////////////////

	class File : public Object
	{

	public:

		File();

		operator WDFFILEOBJECT ();

		virtual ~File();

	protected:

		WDFFILEOBJECT mWdfFileObject;

	private:

	};

}