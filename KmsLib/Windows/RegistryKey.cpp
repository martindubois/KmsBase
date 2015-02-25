
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

		// aSubKey	: [in]
		//
		// Return :
		//	false	= The sub key does not exist / La sous cle n'existe pas
		//	true	= The sub key exists / La sous cle existe
		//
		// Exception : KmsLib::Exception
		bool RegistryKey::DoesSubKeyExist(const char * aSubKey)
		{
			assert(NULL != aSubKey);
			
			assert(NULL != mKey);

			HKEY lKey;

			LSTATUS lRetS = RegOpenKey(mKey, aSubKey, &lKey);
			switch (lRetS)
			{
			case ERROR_SUCCESS :
				assert(NULL != lKey);

				lRetS = RegCloseKey(lKey);
				if (ERROR_SUCCESS != lRetS)
				{
					// NOTE TESTED : Realy not easy to test / Vraiment pas facile a tester
					char lMsg[2048];

					sprintf_s(lMsg, "An error occured when closing the sub key %s", aSubKey);

					throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegCloseKey(  ) failed", lMsg, __FILE__, __FUNCTION__, __LINE__, lRetS);
				}
				return true;

			case ERROR_FILE_NOT_FOUND :
				break;

			default:
				throw new Exception(Exception::CODE_REGISTRY_ERROR, "RegOpenKey( , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, lRetS);
			}

			return false;
		}

		// aName			:	[in,opt]
		// aDefaultValue	:
		DWORD RegistryKey::GetValue_DWORD(const char * aName, DWORD aDefaultValue)
		{
			assert(NULL != mKey);

			DWORD lResult						;
			DWORD lSize_byte = sizeof(lResult)	;
			DWORD lType							;

			LSTATUS lRetS = RegQueryValueEx(mKey, aName, NULL, &lType, reinterpret_cast<LPBYTE>(&lResult), &lSize_byte);
			switch (lRetS)
			{
			case ERROR_SUCCESS :
				if ((REG_DWORD != lType) || (sizeof(lResult) != lSize_byte))
				{
					throw new KmsLib::Exception(KmsLib::Exception::CODE_REGISTRY_ERROR, "Invalid registry value",
						NULL, __FILE__, __FUNCTION__, __LINE__, lType);
				}
				break;

			case ERROR_FILE_NOT_FOUND :
				lResult = aDefaultValue;
				break;

			default :
				throw new KmsLib::Exception(KmsLib::Exception::CODE_REGISTRY_ERROR, "Registry error",
					NULL, __FILE__, __FUNCTION__, __LINE__, lRetS);
			}

			return lResult;
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
				// NOTE TESTED : Realy not easy to test / Vraiment pas facile a tester
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

		// aDevInfoSet	: [in]	Information set containing aDevInfoData /
		//						L'ensemble d'information contenant aDevInfoData
		// aDevInfoData	: [in]	Information about the device / Information au
		//						sujet du peripherique
		// aKeyType		:		See / Voir DIREG_...
		//
		// Exception :	KmsLib::Exception	CODE_REGISTRY_ERROR
		void RegistryKey::Open(HDEVINFO aDevInfoSet, PSP_DEVINFO_DATA aDevInfoData, DWORD aKeyType)
		{
			assert(NULL != aDevInfoSet	);
			assert(NULL != aDevInfoData	);

			if (NULL != mKey)
			{
				Close();
			}

			mKey = SetupDiOpenDevRegKey(aDevInfoSet, aDevInfoData, 0, 0, KEY_READ | KEY_WRITE, aKeyType);
			if (INVALID_HANDLE_VALUE == mKey)
			{
				// This class use NULL, not INVALID_HANDLE_VALUE / Cette
				// classe utilise NULL et non INVALID_HANDLE_VALUE.
				mKey = NULL;

				throw new Exception(Exception::CODE_REGISTRY_ERROR, "SetupDiOpenDevRegKey( , , , , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, aKeyType);
			}

			// NOT TESTED :
		}

	}

}
