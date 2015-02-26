
// Author / Auteur		:	KMS -		Martin Dubois
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/KmsLib/Windows/RegistryKey.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== Windows =============================================================
#include <Windows.h>

#include <SetupAPI.h>

namespace KmsLib
{
	namespace Windows
	{

		// Class / Classe
		/////////////////////////////////////////////////////////////////////

		class RegistryKey
		{

		public:

			enum
			{
				OPEN_FLAG_ADMINISTRATOR	= 0x00000001,
				OPEN_FLAG_DRIVER_KEY	= 0x00000002,
			};

			RegistryKey();

			~RegistryKey();

			operator HKEY ();

			bool	DoesSubKeyExist	(const char * aSubKey);

			DWORD	GetValue_DWORD	(const char * aName, DWORD aDefaultValue);

			void SetDefaultValue(const char						  * aValue);
			void SetValue		(const char * aName, DWORD			aValue);
			void SetValue		(const char * aName, const char   * aValue);
			void SetValue		(const char * aName, DWORD aType, const void * aValue, unsigned int aValueSize_byte);

			void Close			();
			void Create			(HKEY aKey, const char * aSubKey);
			void DeleteSubKey	(const char * aSubKey);
			void DeleteValue	(const char * aName);
			void Open			(HKEY aKey, const char * aSubKey);
			void Open			(HDEVINFO aDevInfoSet, PSP_DEVINFO_DATA aDevInfoData, unsigned int aFlags);

		private:

			RegistryKey(const RegistryKey &);

			const RegistryKey & operator = (const RegistryKey &);

			HKEY	mKey;

		};

	}
}
