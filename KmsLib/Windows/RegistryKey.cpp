
// Auteur	: KMS -		Martin Dubois, ing.
// Projet	: KmsBase
// Fichier	: KmsLib/Windows/RegistryKey.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/Windows/RegistryKey.h>

namespace KmsLib
{
	namespace Windows
	{
		// Public
		/////////////////////////////////////////////////////////////////////

		// Constructeur par defaut
		RegistryKey::RegistryKey() : mKey( NULL )
		{
		}

		// Destructeur
		//
		// Exception : KmsLib::Exception
		RegistryKey::~RegistryKey()
		{
			if (NULL != mKey)
			{
				Close();
			}

			assert(NULL == mKey);
		}

		// Cast operator
		RegistryKey::operator HKEY ()
		{
			assert(NULL != mKey);

			return mKey;
		}

		// aValue	: [in]	
		//
		// Exception : KmsLib::Exception
		void RegistryKey::SetDefaultValue(const char * aValue)
		{
			assert(NULL != aValue);

			SetValue(NULL, aValue);
		}

		// aName	: [in]	Nom de la valeur
		// aValue	:		La valeur
		//
		// Exception : KmsLib::Exception
		void RegistryKey::SetValue(const char * aName, DWORD aValue)
		{
			assert(NULL != aName);

			SetValue(aName, REG_DWORD, &aValue, sizeof(DWORD));
		}

		// aName	: [in,opt]	Nom de la valeur
		// aValue	: [in    ]	La valeur
		//
		// Exception : KmsLib::Exception
		void RegistryKey::SetValue(const char * aName, const char * aValue)
		{
			assert(NULL != aValue	);

			SetValue(aName, REG_SZ, aValue, static_cast< unsigned int >( strlen(aValue) ) + 1);
		}

		// aName			: [in]	Le nom de la valeur
		// aType			:		Le type de la valeur. Voir REG_...
		// aValue			: [in]	La valeur
		// aValueSize_byte	:		La taille de la valeur
		//
		// Exception	: KmsLib::Exception
		void RegistryKey::SetValue(const char * aName, DWORD aType, const void * aValue, unsigned int aValueSize_byte)
		{
			assert(NULL != mKey);

			LSTATUS lRet = RegSetValueEx(mKey, aName, 0, aType, reinterpret_cast< const BYTE * >(aValue), aValueSize_byte);
			if (ERROR_SUCCESS != lRet)
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "RegSetValueEx( 0x%08x, \"%s\", , 0x%08x, , %u bytes ) failed\n",
					reinterpret_cast<unsigned int>(mKey), aName, aType, aValueSize_byte);

				throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegSetValueEx( , , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}

		// Fermer la cle
		//
		// Exception : KmsLib::Exception
		void RegistryKey::Close()
		{
			assert(NULL != mKey);

			LSTATUS lRet = RegCloseKey(mKey);

			mKey = NULL;

			if (ERROR_SUCCESS != lRet)
			{
				// PAS TESTE : Difficile de faire echouer RegCloseKey.
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "RegCloseKey( 0x%08x ) failed",
					reinterpret_cast<unsigned int>(mKey));

				throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegCloseKey(  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}

		// aKey		:		La cle parent
		// aSubKey	: [in]	Le nom de la sous cle
		//
		// Exception : KmsLib::Exception
		void RegistryKey::Create(HKEY aKey, const char * aSubKey)
		{
			assert(NULL != aKey		);
			assert(NULL != aSubKey	);

			if (NULL != mKey)
			{
				Close();
			}

			LSTATUS lRet = RegCreateKeyEx(aKey, aSubKey, 0, NULL, 0, KEY_READ | KEY_WRITE, NULL, &mKey, NULL);
			if (ERROR_SUCCESS != lRet)
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "RegCreateKeyEx( 0x%08x, \"%s\", , , , , , ,  ) failed",
					reinterpret_cast<unsigned int>(aKey), aSubKey);

				throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegCreateKeyEx( , , , , , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lRet);
			}

			assert(NULL != mKey);
		}

		// aSubKey	: [in]
		//
		// Exception : KmsLib::Exception
		void RegistryKey::DeleteSubKey(const char * aSubKey)
		{
			assert(NULL != aSubKey);
			
			assert(NULL != mKey);

			LSTATUS lRet = RegDeleteKey(mKey, aSubKey);
			if (ERROR_SUCCESS != lRet)
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "RegDeleteKey( 0x%08x, \"%s\" ) failed",
					reinterpret_cast<unsigned int>(mKey), aSubKey);

				throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegDeleteKey( ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}

		// aName	: [in]
		//
		// Exception : KmsLib::Exception
		void RegistryKey::DeleteValue(const char * aName)
		{
			assert(NULL != aName);

			assert(NULL != mKey);

			LSTATUS lRet = RegDeleteValue(mKey, aName);
			if (ERROR_SUCCESS != lRet)
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "RegDeleteValue( 0x%08x, \"%s\" ) failed",
					reinterpret_cast<unsigned int>(mKey), aName);

				throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegDeleteValue( ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lRet);
			}
		}

		// aKey		:		La cle parent
		// aSubKey	: [in]	Le nom de la sous cle
		//
		// Exception : KmsLib::Exception
		void RegistryKey::Open(HKEY aKey, const char * aSubKey)
		{
			assert(NULL != aKey);
			assert(NULL != aSubKey);

			if (NULL != mKey)
			{
				Close();
			}

			LSTATUS lRet = RegOpenKeyEx(aKey, aSubKey, 0, KEY_READ | KEY_WRITE, &mKey);
			if (ERROR_SUCCESS != lRet)
			{
				char lMessage[2048];

				sprintf_s(lMessage, sizeof(lMessage), "RegOpenKeyEx( 0x%08x, \"%s\", , ,  ) failed",
					reinterpret_cast<unsigned int>(aKey), aSubKey);

				throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegOpenKeyEx( , , , ,  ) failed",
					lMessage, __FILE__, __FUNCTION__, __LINE__, lRet);
			}

			assert(NULL != mKey);
		}

	}

}
