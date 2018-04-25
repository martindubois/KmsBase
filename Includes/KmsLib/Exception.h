
// Product / Produit  KmsBase

/// \author  KMS - Martin Dubois, ing.
/// \file    Includes/KmsLib/Exception.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

// ===== C++ ================================================================
#include <exception>
#include <string>

// ===== Windows ============================================================
#ifdef GetMessage
    #undef GetMessage
#endif // GetMessage

namespace KmsLib
{

    // Class / Classe
    /////////////////////////////////////////////////////////////////////////

    // ==============
    // std::exception
    // ==============
    //       ^
    //       :
    //   =========                 ===========
    //   Exception @---mMessage--- std::string
    //   =========                 ===========

    /// \cond    en
    /// \brief   Contains information about an exception
    /// \endcond
    /// \cond    fr
    /// \brief   Contient les information au sujet d'un exception
    /// \endcond
    class Exception : public std::exception
    {

    public:

        /// \cond   en
        /// \brief  Exception code
        /// \endcond
        /// \cond   fr
        /// \brief  Code de l'exception
        /// \endcond
        typedef enum
        {
            // ----- 2.0 ----------------------------------------------------
            CODE_IO_ERROR          = 0,
            CODE_IOCTL_ERROR       = 1,
            CODE_NO_SUCH_DEVICE    = 2,
            CODE_NOT_ENOUGH_MEMORY = 3,
            CODE_PRIVATE           = 4,
            CODE_REGISTRY_ERROR    = 5,
            CODE_SETUP_API_ERROR   = 6,
            CODE_UNKNOWN           = 7,
            CODE_USER_ERROR        = 8,

            // ----- 2.1 ----------------------------------------------------
            CODE_AUTHENTIFICATION_ERROR	=  9,
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
            CODE_SERVICE_MANAGER_ERROR = 31,
            CODE_SYSTEM_LOG_ERROR      = 32,

            // ----- 2.3 ----------------------------------------------------
            CODE_ACCESS_VIOLATION		= 33,
            CODE_INTEGER_DIVIDE_BY_ZERO	= 34,
            CODE_INVALID_COMMAND_LINE	= 35,
            CODE_OPEN_CL_ERROR			= 36,
            CODE_STRUCTURED_EXCEPTION	= 37,

            // ----- 2.6 ----------------------------------------------------
            CODE_CLOSE_HANDLE_ERROR  = 38,
            CODE_BUFFER_TOO_SMALL    = 39,
            CODE_COM_PORT_ERROR      = 40,
            CODE_COPY_FILE_ERROR     = 41,
            CODE_CREATE_FILE_ERROR   = 42,
            CODE_DELETE_FILE_ERROR   = 43,
            CODE_DENIED              = 44,
            CODE_DIRECTORY_ERROR     = 45,
            CODE_ERROR               = 46,
            CODE_FILE_OPEN_ERROR     = 47,
            CODE_FILE_READ_ERROR     = 48,
            CODE_FILE_WRITE_ERROR    = 49,
            CODE_INVALID_ADDRESS     = 50,
            CODE_INVALID_PARAMETER   = 51,
            CODE_INVALID_PORT_NUMBER = 52,
            CODE_IO_CANCEL_ERROR     = 53,
            CODE_MOVE_FILE_ERROR     = 54,
            CODE_NO_COM_PORT         = 55,
            CODE_NOT_IMPLEMENTED     = 56,
            CODE_READ_FILE_ERROR     = 57,
            CODE_REG_CLOSE_ERROR     = 58,
            CODE_REG_CREATE_ERROR    = 59,
            CODE_REG_DELETE_ERROR    = 60,
            CODE_REG_OPEN_ERROR      = 61,
            CODE_REG_QUERY_ERROR     = 62,
            CODE_REG_SET_ERROR       = 63,
            CODE_SOCKET_ERROR        = 64,
            CODE_TO_DEFINE           = 65,
            CODE_UNSUCCESSFUL        = 66,
            CODE_WINSOCK_ERROR       = 67,
            CODE_WRITE_FILE_ERROR    = 68,

            CODE_QTY = 69
        }
        Code;

        // Version 2.3

        /// \cond    en
        /// \brief   Register a structured exception translator
        /// \return  This method returns the previous translater
        /// \endcond
        /// \cond    fr
        /// \brief   Enregistre un traducteur d'exceptions structures
        /// \return  Le traducteur precedant
        /// \endcond
        static void * RegisterTranslator();

        /// \cond   en
        /// \brief  Restore a structured exception handler
        /// \param  aTranslator  [-K-;--X]  Value previously returned by
        ///                                 RegisterTranslator
        /// \endcond
        /// \cond   fr
        /// \brief  Reactive un traducteur d'exceptions structures
        /// \param  aTranslator  [-K-;--X]  Valeur precedement retoutne
        ///                                 par RegisterTranslator
        /// \endcond
        static void RestoreTranslator(void * aTranslator);

        // Version  2.6

        /// \cond    en
        /// \brief   Get the name of a code
        /// \param   aCode  The code
        /// \return  This method returns a constant address or NULL if the
        ///          code is not valid
        /// \endcond
        /// \cond    fr
        /// \brief	 Obtenir le nom d'un code
        /// \param   aCode  Le code
        /// \return  Cette methode retourne l'adresse d'une constante ou
        ///          NULL si le code n'est pas valid
        /// \endcond
        static const char * GetCodeName(Code aCode);

        /// \cond   en
        /// \brief  Constructor
        /// \param  aCode                 See Code
        /// \param  aWhat      [-K-;R--]  Simple message
        /// \param  aMessage   [--O;R--]  Message
        /// \param  aFile      [-K-;R--]  Source file name
        /// \param  aFunction  [-K-;R--]  Function name
        /// \param  aLine                 Line number
        /// \param  aInfoA                Information that depends on the
        ///                               exception
        /// \endcond
        /// \cond   fr
        /// \brief  Constructeur
        /// \param  aCode                 Voir Code
        /// \param  aWhat      [-K-;R--]  Message simple
        /// \param  aMessage   [--O;R--]  Message
        /// \param  aFile      [-K-;R--]  Nom du fichier sources
        /// \param  aFunction  [-K-;R--]  Nom de la fonction
        /// \param  aLine                 Numero de la ligne dans le
        ///                               fichier source
        /// \param  aInfoA                Information qui depend de
        ///                               l'exception
        /// \endcond
        Exception(Code aCode, const char * aWhat, const char * aMessage, const char * aFile, const char * aFunction, unsigned int aLine, unsigned int aInfoA);

        /// \cond	 en
        /// \brief	 Returns the exception code
        /// \return  See CODE_...
        /// \endcond
        /// \cond	 fr
        /// \brief	 Retourne le code de l'exception
        /// \return  Voir CODE_...
        /// \endcond
        Code GetCode() const;

        /// \cond    en
        /// \brief   Returns the source file name
        /// \return  The source file name
        /// \endcond
        /// \cond    fr
        /// \brief   Retourne le nom du fichier source
        /// \return  Le nom du fichier source
        /// \endcond
        const char * GetFile() const;

        /// \cond    en
        /// \brief   Returns the function name
        /// \return  The function name
        /// \endcond
        /// \cond    fr
        /// \brief   Retourne le nom de la fonction
        /// \return  Le nom de la fonction
        /// \endcond
        const char * GetFunction() const;

        /// \cond    en
        /// \brief   Returns the information A
        /// \return  The information A
        /// \endcond
        /// \cond    fr
        /// \brief   Retourne l'information A
        /// \return  L'information A
        /// \endcond
        unsigned int GetInfoA() const;

        /// \cond    en
        /// \brief   Returns the last Windows error information
        /// \return  The last Windows error information
        /// \endcond
        /// \cond    fr
        /// \brief   Retourne l'information sur la derniere erreur Windows
        /// \return  L'information sur la derniere erreur Windows
        /// \endcond
        unsigned int GetLastError() const;

        /// \cond    en
        /// \brief   Returns the line number
        /// \return  The line number
        /// \endcond
        /// \cond    fr
        /// \brief   Retourne le numero de la ligne dans le fichier source
        ///	\return  Le numero de la ligne dans le fichier source
        /// \endcond
        unsigned int GetLine() const;

        /// \cond    en
        /// \brief   Returns the error message
        /// \return  A pointer to an internal buffer
        /// \endcond
        /// \cond    fr
        /// \brief   Retourne le message d'erreur
        ///	\return  Un pointeur vers un espace memoire interne
        /// \endcond
        const char * GetMessage() const;

        /// \cond   en
        /// \brief  Write the exception into a stream
        /// \param  aFile  [---;R--]  The stream to write to
        /// \endcond
        /// \cond   fr
        /// \brief  Ecrit l'exception dans un fichier
        ///	\param  aFile  [---;R--]  Le fichier dans lequel ecrire
        /// \endcond
        void Write(FILE * aFile) const;

        // ===== std::exception ========================================

        /// \cond   en
        /// \brief  See std::exception
        /// \endcond
        /// \cond   fr
        /// \brief  Voir std::exception
        /// \endcond
        virtual ~Exception() throw ();

        /// \cond   en
        /// \brief  See std::exception
        /// \endcond
        /// \cond   fr
        /// \brief  Voir std::exception
        /// \endcond
        virtual const char * what() const throw ();

    private:

        Code         mCode     ;
        const char * mFile     ;
        const char * mFunction ;
        unsigned int mInfoA    ;
        unsigned int mLastError;
        unsigned int mLine     ;
        std::string  mMessage  ;
        const char * mWhat     ;

    };

    // Public
    /////////////////////////////////////////////////////////////////////////

    inline Exception::Code Exception::GetCode() const
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
