
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

	// ----- 2.2 ----------------------------------------------------
	"CODE_ACCESS_VIOLATION"			,
	"CODE_INTEGER_DIVIDE_BY_ZERO"	,
	"CODE_STRUCTURED_EXCEPTION"		,
};

// Static method declarations / Declaration des fonctions statique
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points / Points d'entres =====================================

static void TranslateException(unsigned int aCode, struct _EXCEPTION_POINTERS * aStruct );

namespace KmsLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	void * Exception::RegisterTranslator()
	{
		return _set_se_translator(TranslateException);
	}

	void Exception::RestoreTranslator(void * aTranslator)
	{
		void * lTranslator = _set_se_translator(reinterpret_cast<_se_translator_function>(aTranslator));
		assert(TranslateException == lTranslator);
	}

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
			// NOT TESTED : Not easy to test / Pas facile a tester
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

// Static functions / Fonction statiques
/////////////////////////////////////////////////////////////////////////////

// ===== Entry points / Points d'entres =====================================

void TranslateException(unsigned int aCode, struct _EXCEPTION_POINTERS * aStruct )
{
	assert(NULL != aStruct);

	KmsLib::Exception::Code	lCode	;
	const char			  * lMsg	;

	switch (aCode)
	{
	case 0xc0000005: lCode = KmsLib::Exception::CODE_ACCESS_VIOLATION		; lMsg = "Access violation"		; break;
	case 0xc0000094: lCode = KmsLib::Exception::CODE_INTEGER_DIVIDE_BY_ZERO	; lMsg = "Integet divide by 0"	; break;

	default:
		// NOT TESTED : Not easy to test / Pas facile a tester
		lCode = KmsLib::Exception::CODE_STRUCTURED_EXCEPTION; lMsg = "Structured exception";
	}

	throw new KmsLib::Exception(lCode, lMsg, NULL, __FILE__, __FUNCTION__, __LINE__, aCode);
}
