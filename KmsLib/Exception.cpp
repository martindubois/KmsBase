
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// File		:	KmsLib/Exception.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>

// ===== Interfaces =========================================================
#include <KmsLib/Exception.h>

// Constantes
/////////////////////////////////////////////////////////////////////////////

static const char * CODE_NAMES[ KmsLib::Exception::CODE_QTY ] =
{
	// ----- 2.0 -------------------------------------------------------------
	"CODE_IO_ERROR"				,
	"CODE_IOCTL_ERROR"			,
	"CODE_NO_SUCH_DEVICE"		,
	"CODE_NOT_ENOUGH_MEMORY"	,
	"CODE_PRIVATE"				,
	"CODE_REGISTRY_ERROR"		,
	"CODE_SETUP_API_ERROR"		,
	"CODE_UNKNOWN"				,
	"CODE_USER_ERROR"			,
	
	// ----- 2.1 -------------------------------------------------------------
	"CODE_AUTHENTIFICATION_ERROR"	,
	"CODE_COMMUNICATION_ERROR"		,
	"CODE_GUI_ERROR"				,
	"CODE_HARDWARE_ERROR"			,
	"CODE_INSTALLATION_ERROR"		,
	"CODE_INVALID_ARGUMENT"			,
	"CODE_INVALID_BUFFER_ADDRESS"	,
	"CODE_INVALID_BUFFER_SIZE"		,
	"CODE_INVALID_DATA"				,
	"CODE_INVALID_DATE"				,
	"CODE_INVALID_HANDLE"			,
	"CODE_INVALID_TIME"				,
	"CODE_NETWORK_ERROR"			,
	"CODE_NOT_FOUND"				,
	"CODE_OVERFLOW"					,
	"CODE_PERMISSION_DENIED"		,
	"CODE_PROTOCOL_ERROR"			,
	"CODE_STATE_ERROR"				,
	"CODE_SYSTEM_ERROR"				,
	"CODE_THREAD_ERROR"				,
	"CODE_TIMEOUT"					,
	"CODE_UNDERFLOW"				,

	// ----- 2.2 ----------------------------------------------------
	"CODE_SERVICE_MANAGER_ERROR"	,
	"CODE_SYSTEM_LOG_ERROR"			,
};

namespace KmsLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	// aCode		:			Voir CODE_...
	// aWhat		: [in,keep]	Message statique
	// aMessage		: [in     ]	Message dynamique
	// aFile		: [in,keep]	Fichier source
	// aFunction	: [in,keep]	Nom de la fonction
	// aLine		:			Numero de ligne dans le fichier source
	// aInfoA		:			Infomation dont la signification depend de
	//							l'exception.
	Exception::Exception(Code aCode, const char * aWhat, const char * aMessage, const char * aFile, const char * aFunction, unsigned int aLine, unsigned int aInfoA) :
		mCode		(aCode			),
		mFile		(aFile			),
		mFunction	(aFunction		),
		mInfoA		(aInfoA			),
		mLastError	(GetLastError()	),
		mLine		(aLine			),
		mWhat		(aWhat			)
	{
		assert(NULL !=	aFile		);
		assert(NULL !=	aFunction	);
		assert(0	<	aLine		);
		assert(NULL !=  aWhat		);

		if (NULL != aMessage)
		{
			mMessage = aMessage;
		}
	}

	// Retour : Le nom du fichier source
	const char * Exception::GetFile() const
	{
		assert(NULL != mFile);

		return mFile;
	}

	// Retour : Le nom de la fonction
	const char * Exception::GetFunction() const
	{
		return mFunction;
	}

	// Retour : Le numero de ligne dans le fichier source
	unsigned int Exception::GetLine() const
	{
		return mLine;
	}

	void Exception::Write(FILE * aFile) const
	{
		assert(NULL != aFile);

		fprintf(aFile,
			"    Exception - ");

		if (CODE_QTY > mCode)
		{
			fprintf(aFile, "%s", CODE_NAMES[mCode]);
		}
		else
		{
			fprintf(aFile, "%u (0x%08x)", mCode, mCode);
		}

		fprintf(aFile,
			"\n"
			"        File       : %s (line %u)\n"
			"        Function   : %s\n"
			"        Info A     : %u (0x%08x)\n"
			"        Last error : %u (0x%08x)\n",
			mFile, mLine,
			mFunction,
			mInfoA, mInfoA,
			mLastError, mLastError );

		if (0 < mMessage.size())
		{
			fprintf(aFile,
				"        Message    : %s\n",
				mMessage.c_str());
		}

		fprintf(aFile,
			"        What       : %s\n"
			"\n",
			what());
	}
	
	// ===== std::exception ==================================================
	
	Exception::~Exception() throw ()
	{
	}
	
	const char * Exception::what() const throw ()
	{
		assert(NULL != mWhat);
		
		return mWhat;
	}
	
}
