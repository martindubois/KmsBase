
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/KmsLib/Windows/DriverHandle.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Interface ==========================================================
#include <KmsLib/Windows/FileHandle.h>
#include <KmsLib/Windows/RegistryKey.h>

namespace KmsLib
{

	namespace Windows
	{

		// Class / Classe
		/////////////////////////////////////////////////////////////////////

		class DriverHandle : public FileHandle
		{

		public:

			enum
			{
				CONNECT_FLAG_ADMINISTRATOR		= 0x00000001,
				CONNECT_FLAG_OPEN_DEVICE_KEY	= 0x00000002,
			};

			DriverHandle();

			virtual ~DriverHandle();

			void	CancelAll();

			void	Connect(const char * aLink		, DWORD aDesiredAccess						);
			void	Connect(const GUID & aInterface	, DWORD aDesiredAccess, unsigned int aFlags	);

			unsigned int	Control(unsigned int aCode, const void * aIn, unsigned int aInSize_byte, void * aOut, unsigned int aOutSize_byte);

			RegistryKey	mDeviceKey;

		private:

			DriverHandle(const DriverHandle &);

			const DriverHandle & operator = (const DriverHandle &);

		};

	}

}
