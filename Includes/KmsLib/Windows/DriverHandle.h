
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/KmsLib/Windows/DriverHandle.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Interface ==========================================================
#include <KmsLib/Windows/FileHandle.h>

namespace KmsLib
{

	namespace Windows
	{

		// Class
		/////////////////////////////////////////////////////////////////////

		class DriverHandle : public FileHandle
		{

		public:

			DriverHandle();

			virtual ~DriverHandle();

			void	CancelAll();

			void	Connect(const char * aLink		, DWORD aDesiredAccess	);
			void	Connect(const GUID & aInterface	, DWORD aDesiredAccess	);

			unsigned int	Control(unsigned int aCode, const void * aIn, unsigned int aInSize_byte, void * aOut, unsigned int aOutSize_byte);

		private:

			DriverHandle(const DriverHandle &);

			const DriverHandle & operator = (const DriverHandle &);

		};

	}

}
