
// Product / Produit	:	KmsBase

/// \author	KMS -	Martin Dubois, ing.
/// \file	Includes/KmsLib/Exception.h

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

	// Class / Classe
	/////////////////////////////////////////////////////////////////////////

	/// \cond	en
	/// \brief	Contains information about an exception
	/// \endcond
	/// \cond	fr
	/// \brief	Contient les information au sujet d'un exception
	/// \endcond
	class Exception : public std::exception
	{
		
	public:

		/// \cond	en
		/// \brief	Exception code
		/// \endcond
		/// \cond	fr
		/// \brief	Code de l'exception
		/// \endcond
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

			// ----- 2.3 ----------------------------------------------------
			CODE_ACCESS_VIOLATION		= 33,
			CODE_INTEGER_DIVIDE_BY_ZERO	= 34,
			CODE_INVALID_COMMAND_LINE	= 35,
			CODE_STRUCTURED_EXCEPTION	= 36,

			CODE_QTY = 37
		}
		Code;
		
		// Version 2.3

		/// \cond	en
		/// \brief	Register a structured exception translator
		/// \return	This method returns the previous translater
		/// \endcond
		/// \cond	fr
		/// \brief	Enregistre un traducteur d'exceptions structures
		/// \return	Le traducteur precefant
		/// \endcond
		static void	  * RegisterTranslator();

		/// \cond	en
		/// \brief	Restore a structured exception handler
		/// \param	aTranlsator	Value previously returned by RegisterTranslator
		/// \endcond
		/// \cond	fr
		/// \brief	Reactive un traducteur d'exceptions structures
		/// \param	aTranslator	Valeur precedement retoutne par RegisterTranslator
		/// \endcond
		static void		RestoreTranslator(void * aTranslator);

		/// \cond	en
		/// \brief	Constructor
		/// \param	aCode		See Code
		/// \param	aWhat		[in,keep]	Simple message
		/// \param	aMessage	[in]		Message
		/// \param	aFile		[in]		Source file name
		/// \param	aFunction	[in]		Function name
		/// \param	aLine					Line number
		/// \param	aInfoA					Information that depends on the exception
		/// \endcond
		/// \cond	fr
		/// \brief	Constructeur
		/// \param	aCode					Voir Code
		/// \param	aWhat		[in,keep]	Message simple
		/// \param	aMessage	[in]		Message
		/// \param	aFile		[in]		Nom du fichier sources
		/// \param	aFunction	[in]		Nom de la fonction
		/// \param	aLine					Numero de la ligne dans le fichier source
		/// \param	aInfoA					Information qui depend de l'exception
		/// \endcond
		Exception(Code aCode, const char * aWhat, const char * aMessage, const char * aFile, const char * aFunction, unsigned int aLine, unsigned int aInfoA);

		Code			GetCode() const;

		/// \cond	en
		/// \brief	Returns the source file name
		/// \return	The source file name
		/// \endcond
		/// \cond	fr
		/// \brief	Retourne le nom du fichier source
		/// \return	Le nom du fichier source
		/// \endcond
		const char    * GetFile() const;

		/// \cond	en
		/// \brief	Returns the function name
		/// \return	The function name
		/// \endcond
		/// \cond	fr
		/// \brief	Retourne le nom de la fonction
		/// \return	Le nom de la fonction
		/// \endcond
		const char    * GetFunction() const;

		unsigned int	GetInfoA() const;

		unsigned int	GetLastError() const;

		/// \cond	en
		/// \brief	Returns the line number
		/// \return	The line number
		/// \endcond
		/// \cond	fr
		/// \brief	Retourne le numero de la ligne dans le fichier source
		///	\return	Le numero de la ligne dans le fichier source
		/// \endcond
		unsigned int	GetLine() const;

		const char    * GetMessage() const;

		/// \cond	en
		/// \brief	Write the exception into a stream
		/// \param	aFile	[in,out]	The stream to write to
		/// \endcond
		/// \cond	fr
		/// \brief	Ecrit l'exception dans un fichier
		///	\param	aFile	[in,out]	Le fichier dans lequel ecrire
		/// \endcond
		void	Write(FILE * aFile) const;
		
		// ===== std::exception ========================================

		/// \cond	en
		/// \brief	See std::exception
		/// \endcond
		/// \cond	fr
		/// \brief	Voir std::exception
		/// \endcond
		virtual	~Exception() throw ();

		/// \cond	en
		/// \brief	See std::exception
		/// \endcond
		/// \cond	fr
		/// \brief	Voir std::exception
		/// \endcond
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

	/// \cond	en
	/// \brief	Code accessor
	/// \return	See CODE_...
	/// \endcond
	/// \cond	fr
	/// \brief	Accesseur pour le code
	/// \retval	Voir CODE_...
	/// \endcond
	inline Exception::Code	Exception::GetCode() const
	{
		return mCode;
	}

	/// \cond	en
	/// \brief	Information A accessor
	/// \return	The A information
	/// \endcond
	/// \cond	fr
	/// \brief	Accesseur pour l'information A
	/// \return	L'information A
	/// \endcond
	inline unsigned int Exception::GetInfoA() const
	{
		return mInfoA;
	}

	/// \cond	en
	/// \brief	Last error accessor
	/// \return	This method return the last value GetLastError returned.
	/// \endcond
	/// \cond	fr
	/// \brief	Accesseur pour la derniere erreur
	/// \return	Cette method retourne la derniere valeur retourner par
	///			GetLastError.
	/// \endcond
	inline unsigned int Exception::GetLastError() const
	{
		return mLastError;
	}

	/// \cond	en
	/// \brief	Message accessor
	/// \return	This method returns the address of an internal storage.
	/// \endcond
	/// \cond	fr
	/// \brief	Accesseur pour le message
	/// \return	Cette methode retourne un pointeur vers un implacement
	///			interne.
	/// \endcond
	inline const char * Exception::GetMessage() const
	{
		return (0 < mMessage.size()) ? mMessage.c_str() : what();
	}

}
