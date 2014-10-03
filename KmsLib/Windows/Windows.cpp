
// Auteur	: KMS -		Martin Dubois, ing.
// Projet	: KmsBase
// Fichier	: KmsLib/Windows/Windows.h

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Interface ==========================================================
#include <KmsLib/Windows/RegistryKey.h>

#include <KmsLib/Windows/Windows.h>

namespace KmsLib
{
	namespace Windows
	{

		// Constantes
		/////////////////////////////////////////////////////////////////////

		const char * COMMAND_EDIT = "Edit";
		const char * COMMAND_OPEN = "Open";

		// Fonctions
		/////////////////////////////////////////////////////////////////////

		// aExt			: [in]
		// aClassId		: [in]
		// aCommandName : [in]	See COMMAND_...
		// aCommand		: [in]
		//
		// Exception : KmsLib::Exception
		void Extension_Register(const char * aExt,
			const char * aClassId, const char * aCommandName, const char * aCommand)
		{
			assert(NULL != aExt			);
			assert(NULL != aClassId		);
			assert(NULL != aCommandName	);
			assert(NULL != aCommand		);

			RegistryKey	lKey;

			lKey.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Classes");

			int		lResult = 0;

			RegistryKey	lKey0;
			RegistryKey	lKey1;

			lKey0.Create(lKey, aExt		);
			lKey1.Create(lKey, aClassId	);

			lKey.Close();

			RegistryKey	lKey2;
			RegistryKey	lKey3;

			lKey2.Create(lKey0, "OpenWithProgIds"	);
			lKey3.Create(lKey1, "shell"				);

			lKey0.Close();
			lKey1.Close();

			lKey2.SetValue	(aClassId, REG_BINARY, NULL, 0);
			lKey1.Create	(lKey3, aCommandName);

			lKey2.Close();
			lKey3.Close();

			lKey3.Create(lKey1, "command");

			lKey1.Close();

			lKey3.SetDefaultValue(aCommand);

			lKey3.Close();
		}

		// aExt			: [in]
		// aClassId		: [in]
		// aCommandName : [in]	See COMMAND_...
		//
		// Exception : KmsLib::Exception
		void Extension_Unregister(const char * aExt, const char * aClassId, const char * aCommandName)
		{
			assert(NULL != aExt);
			assert(NULL != aClassId);
			assert(NULL != aCommandName);

			RegistryKey	lKey;

			lKey.Open(HKEY_LOCAL_MACHINE, "SOFTWARE\\Classes");

			int		lResult = 0;

			RegistryKey	lKey0;
			RegistryKey	lKey1;

			lKey0.Open(lKey, aExt		);
			lKey1.Open(lKey, aClassId	);

			lKey.Close();

			RegistryKey	lKey2;
			RegistryKey	lKey3;

			lKey2.Open(lKey0, "OpenWithProgIds"	);
			lKey3.Open(lKey1, "shell"			);

			lKey0.Close();
			lKey1.Close();

			lKey2.DeleteValue	(aClassId		);
			lKey1.DeleteSubKey	(aCommandName	);

			lKey2.Close();
			lKey3.Close();
		}

	}
}