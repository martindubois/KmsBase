
// Auteur	: KMS -		Martin Dubois
// Projet	: KmsBase
// Fichier	: Includes/KmsLib/Windows/RegistryKey.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== System =============================================================
#include <Windows.h>

namespace KmsLib
{
	namespace Windows
	{

		// Classe
		/////////////////////////////////////////////////////////////////////

		class RegistryKey
		{

		public:

			RegistryKey();

			~RegistryKey();

			operator HKEY ();

			void SetDefaultValue(const char						  * aValue);
			void SetValue		(const char * aName, DWORD			aValue);
			void SetValue		(const char * aName, const char   * aValue);
			void SetValue		(const char * aName, DWORD aType, const void * aValue, unsigned int aValueSize_byte);


			void Close			();
			void Create			(HKEY aKey, const char * aSubKey);
			void DeleteSubKey	(const char * aSubKey);
			void DeleteValue	(const char * aName);
			void Open			(HKEY aKey, const char * aSubKey);

		private:

			HKEY	mKey;

		};
	}
}
