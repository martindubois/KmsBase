
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	Includes/KmsLib/Exception.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>
#include <string>

namespace KmsLib
{

	// Class
	/////////////////////////////////////////////////////////////////////////

	class Exception : public std::exception
	{
		
	public:

		typedef enum
		{
			// ----- 2.0 ----------------------------------------------------
			CODE_IO_ERROR			= 0,
			CODE_IOCTL_ERROR		= 1,
			CODE_NO_SUCH_DEVICE		= 2,
			CODE_NOT_ENOUGH_MEMORY	= 3,
			CODE_PRIVATE			= 4,
			CODE_REGISTRY_ERROR		= 5,
			CODE_SETUP_API_ERROR	= 6,
			CODE_UNKNOWN			= 7,
			CODE_USER_ERROR			= 8,

			// ----- 2.1 ----------------------------------------------------
			CODE_AUTHENTIFICATION_ERROR	= 9 ,
			CODE_COMMUNICATION_ERROR	= 10,
			CODE_GUI_ERROR				= 11,
			CODE_HARDWARE_ERROR			= 12,
			CODE_INSTALLATION_ERROR		= 13,
			CODE_INVALID_ARGUMENT		= 14,
			CODE_INVALID_BUFFER_ADDRESS	= 15,
			CODE_INVALID_BUFFER_SIZE	= 16,
			CODE_INVALID_DATA			= 17,
			CODE_INVALID_DATE			= 18,
			CODE_INVALID_HANDLE			= 19,
			CODE_INVALID_TIME			= 20,
			CODE_NETWORK_ERROR			= 21,
			CODE_NOT_FOUND				= 22,
			CODE_OVERFLOW				= 23,
			CODE_PERMISSION_DENIED		= 24,
			CODE_PROTOCOL_ERROR			= 25,
			CODE_STATE_ERROR			= 26,
			CODE_SYSTEM_ERROR			= 27,
			CODE_THREAD_ERROR			= 28,
			CODE_TIMEOUT				= 29,
			CODE_UNDERFLOW				= 30,

			// ----- 2.2 ----------------------------------------------------
			CODE_SERVICE_MANAGER_ERROR	= 31,
			CODE_SYSTEM_LOG_ERROR		= 32,

			CODE_QTY	= 33
		}
		Code;
		
		Exception(Code aCode, const char * aWhat, const char * aMessage, const char * aFile, const char * aFunction, unsigned int aLine, unsigned int aInfoA);

		Code			GetCode			() const;
		const char    * GetFile			() const;
		const char    * GetFunction		() const;
		unsigned int	GetInfoA		() const;
		unsigned int	GetLastError	() const;
		unsigned int	GetLine			() const;
		const char    * GetMessage		() const;

		void	Write(FILE * aFile) const;
		
		// ===== std::exception ========================================

		virtual	~Exception() throw ();

		virtual const char * what() const throw ();
		
	private:

		Code			mCode		;
		const char    * mFile		;
		const char    * mFunction	;
		unsigned int	mInfoA		;
		unsigned int	mLastError	;
		unsigned int	mLine		;
		std::string		mMessage	;
		const char	  * mWhat		;

	};

	// Public
	/////////////////////////////////////////////////////////////////////////

	inline Exception::Code	Exception::GetCode() const
	{
		return mCode;
	}

	inline unsigned int Exception::GetInfoA() const
	{
		return mInfoA;
	}

	inline unsigned int Exception::GetLastError() const
	{
		return mLastError;
	}

	inline const char * Exception::GetMessage() const
	{
		return (0 < mMessage.size()) ? mMessage.c_str() : what();
	}

}
