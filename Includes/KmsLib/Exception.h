
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
			CODE_IO_ERROR			= 0,
			CODE_IOCTL_ERROR		= 1,
			CODE_NO_SUCH_DEVICE		= 2,
			CODE_NOT_ENOUGH_MEMORY	= 3,
			CODE_PRIVATE			= 4,
			CODE_REGISTRY_ERROR		= 5,
			CODE_SETUP_API_ERROR	= 6,
			CODE_UNKNOWN			= 7,
			CODE_USER_ERROR			= 8,

			CODE_QTY	= 9
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

	private:

		Code			mCode		;
		const char    * mFile		;
		const char    * mFunction	;
		unsigned int	mInfoA		;
		unsigned int	mLastError	;
		unsigned int	mLine		;
		std::string		mMessage	;

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
