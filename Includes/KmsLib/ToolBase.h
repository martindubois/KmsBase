
// Product / Produit  KmsBase

/// \author  KMS - Martin Dubois, ing.
/// \file    Includes/KmsLib/ToolBase.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== KmsBase =============================================================
#include <KmsLib/Exception.h>

namespace KmsLib
{

    // Class / Classe
    /////////////////////////////////////////////////////////////////////////

    /// \cond   en
    /// \brief  Command line tools base
    /// \todo   AskUser - Make it non static method. If the aFile is NULL,
    ///         use the current input file.
    /// \endcond
    /// \cond   fr
    /// \brief  Base d'un outil en ligne de commande
    /// \todo   AskUser - En faire des method non statique. Si le aFile est
    ///         NULL, utiliser le fichier d'entree courrant.
    /// \endcond
    class ToolBase
    {

    public:

        /// \cond   en
        /// \brief  Type of reported information
        /// \endcond
        /// \cond   fr
        /// \brief  Type des informations raportees
        /// \endcond
        typedef enum
        {
            REPORT_ERROR      ,
            REPORT_FATAL_ERROR,
            REPORT_INFO       ,
            REPORT_OK         ,
            REPORT_USER_ERROR ,
            REPORT_WARNING    ,

            REPORT_QTY
        }
        ReportType;

        /// \cond   en
        /// \brief  Type of function
        /// \endcond
        /// \cond   fr
        /// \brief  Type des fonctions
        /// \endcond
        typedef void(*Function)(ToolBase * aToolBase, const char * aArg);

        /// \cond   en
        /// \brief  Describe a command
        /// \endcond
        /// \cond   fr
        /// \brief  Decrit une commande
        /// \endcond
        typedef struct CommandInfo
        {
            const char               * mName       ;
            Function                   mFunction   ;
            const char               * mHelpLine   ;
            const struct CommandInfo * mSubCommands;
        }
        CommandInfo;

        /// \cond   en
        /// \brief  Ask the user for a unsigned short value
        /// \param  aFile  [---;RW-]  The input stream
        /// \param  aName  [---;R--]  Name of the requested value
        /// \param  aMin              Minimal value
        /// \param  aMax              Maximal value
        /// \param  aDefault          Default value
        /// \param  aOut   [---;-W-]  The value the user entered
        /// \endcond
        /// \cond   fr
        /// \brief  Demande une valeur unsigned short a l'utilisateur
        /// \param  aFile  [---;RW-]  Le fichier d'entree
        /// \param  aName  [---;R--]  Nom de la valeur demandee
        /// \param  aMin              Valeur minimale
        /// \param  aMax              Valeur maximale
        /// \param  aDefault          Valeur par defaut
        /// \param  aOut   [---;-W-]  La valeur que l'utilisateur a entree
        /// \endcond
        /// \exception  Exception  CODE_FILE_READ_ERROR
        static void AskUser(FILE * aFile, const char * aName, unsigned short aMin, unsigned short aMax, unsigned short aDefault, unsigned short * aOut);

        /// \cond   en
        /// \brief  Ask the user for a string value
        /// \param  aFile  [---;RW-]  The input stream
        /// \param  aName  [---;R--]  Name of the requested value
        /// \param  aOut   [---;-W-]  The value the user entered
        /// \param  aOutSize_byte     The value maximal size
        /// \endcond
        /// \cond   fr
        /// \brief  Demande une chaine de caractere a l'utilisateur
        /// \param  aFile  [---;RW-]  Le fichier d'entree
        /// \param  aName  [---;R--]  Nom de la valeur demandee
        /// \param  aOut   [---;-W-]  La valeur que l'utilisateur a
        ///                           entree
        /// \param  aOutSize_byte     La taille maximale de la valeur
        /// \endcond
        /// \exception  Exception  CODE_FILE_READ_ERROR
        static void AskUser(FILE * aFile, const char * aName, char * aOut, unsigned int aOutSize_byte);

        /// \cond	en
        /// \brief  Ask the user for a string value
        /// \param  aFile     [---;RW-]  The input stream
        /// \param  aName     [---;R--]  Name of the requested value
        /// \param  aDefault  [---;R--]  Default value
        /// \param  aOut      [---;-W-]  The value the user entered
        /// \param	aOutSize_byte        The value maximal size
        /// \endcond
        /// \cond   fr
        /// \brief  Demande une chaine de caractere a l'utilisateur
        /// \param	aFile     [---;RW-]  Le fichier d'entree
        /// \param  aName     [---;R--]  Nom de la valeur demandee
        /// \param  aDefault  [---;R--]  Valeur par defaut
        /// \param  aOut      [---;-W-]  La valeur que l'utilisateur a
        ///                              entree
        /// \param	aOutSize_byte        La taille maximale de la
        ///                              valeur
        /// \endcond
        /// \exception  Exception  CODE_FILE_READ_ERROR
        static void AskUser(FILE * aFile, const char * aName, const char * aDefault, char * aOut, unsigned int aOutSize_byte);

        /// \cond	en
        /// \brief  Ask the user for an input file name
        /// \param  aFile  [---;RW-]  The input stream
        /// \param  aName  [---;R--]  Name of the requested value
        /// \param	aOut   [---;-W-]  The value the user entered
        /// \param  aOutSize_byte     The value maximal size
        /// \endcond
        /// \cond   fr
        /// \brief  Demande a l'utilisateur le nom d'un fichier d'entree
        /// \param  aFile  [---;RW-]  Le fichier d'entree
        /// \param  aName  [---;R--]  Nom de la valeur demandee
        /// \param  aOut   [---;-W-]  La valeur que l'utilisateur a
        ///                           entree
        /// \param aOutSize_byte      La taille maximale de la valeur
        /// \endcond
        /// \exception  Exception  CODE_FILE_READ_ERROR
        static void AskUser_InputFileName(FILE * aFile, const char * aName, char * aOut, unsigned int  aOutSize_byte);

        /// \cond   en
        /// \brief  Ask the user for an output file name
        /// \param  aFile     [---;RW-]  The input stream
        /// \param  aName     [---;R--]  Name of the requested value
        /// \param  aDefault  [---;R--]  Default value
        /// \param  aOut      [---;-W-]  The value the user entered
        /// \param  aOutSize_byte        The value maximal size
        /// \endcond
        /// \cond   fr
        /// \brief  Demande a l'utilisateur le nom d'un fichier de
        ///         sortie
        /// \param  aFile     [---;RW-]  Le fichier d'entree
        /// \param  aName     [---;R--]  Nom de la valeur demandee
        /// \param  aDefault  [---;R--]  Valeur par defaut
        /// \param  aOut      [---;-W-]  La valeur que l'utilisateur a
        ///                              entree
        /// \param  aOutSize_byte        La taille maximale de la
        ///                              valeur
        /// \endcond
        /// \exception  Exception  CODE_FILE_READ_ERROR
        static void AskUser_OutputFileName(FILE * aFile, const char * aName, const char * aDefault, char * aOut, unsigned int aOutSize_byte);

        /// \cond   en
        /// \brief  Report a result
        /// \param  aType  See ReportType
        /// \endcond
        /// \cond   fr
        /// \brief  Affiche un resultat
        /// \param  aType  Voir ReportType
        /// \endcond
        static void Report(ReportType aType);

        /// \cond   en
        /// \brief  Report an exception
        /// \param  aType                  See ReportType
        /// \param  aException  [---;R--]  See KmsLib::Exception
        /// \endcond
        /// \cond   fr
        /// \brief  Affiche une exception
        /// \param  aType                  Voir ReportType
        /// \param  aException  [---;R--]  Voir KmsLib::Exception
        /// \endcond
        static void Report(ReportType aType, const KmsLib::Exception * aException);

        /// \cond   en
        /// \brief  Report an error
        /// \param  aType                See ReportType
        /// \param  aMessage  [---;R--]  A simple message
        /// \endcond
        /// \cond   fr
        /// \brief  Affiche une erreur
        /// \param  aType                Voir ReportType
        /// \param  aMessage  [---;R--]  Un message simple
        /// \endcond
        static void Report(ReportType aType, const char * aMessage);

        /// \cond   en
        /// \brief  Constructor
        /// \param  aCommands  [-K-;R--]  The table describing the
        ///                               commands
        /// \endcond
        /// \cond   fr
        /// \brief  Contructor
        ///	\param  aCommands  [-K-;R--]  Le tableau definissant les
        ///                               commandes
        /// \endcond
        ToolBase(const CommandInfo * aCommands);

        /// \cond    en
        /// \brief   Parse the arguments the user passed to the tools
        /// \param   aCount              Argument count
        /// \param   aVector  [---;R--]  Arguments
        /// \retval  false	The method did not execute command
        /// \retval  true	The method executed at least one command
        /// \endcond
        /// \cond	 fr
        /// \brief   Interprete les artuments passees a l'outils par
        ///          l'utilisateur
        /// \param   aCount              Le nombre d'arguments
        /// \param   aVector  [---;R--]  Les arguments
        /// \retval  false	La methode n'a pas execute de commande
        /// \retval  true	La methode a au moins execute une commande
        /// \endcond
        /// \exception  Exception  CODE_INVALID_COMMAND_LINE
        bool ParseArguments(int aCount, const char ** aVector);

        /// \cond   en
        /// \brief  Parse the commands read from the standard input
        /// \endcond
        /// \cond   fr
        /// \brief  Interprete les commandes lues de l'entree standard
        /// \endcond
        /// \exception  Exception  CODE_...
        void ParseCommands();

        /// \cond   en
        /// \brief  Parse the commands read from a file
        /// \param  aFileName  [---;R--]  File name
        /// \endcond
        /// \cond   fr
        /// \brief  Interprete les commandes lues d'un fichier
        /// \param  aFileName  [---;R--]  Nom du fichier
        /// \endcond
        void ParseCommands(const char * aFileName);

        // ===== Function ===================================================

        /// \cond   en
        /// \brief  Execute a script
        /// \param  aToolBase  [---;RW-]  A ToolBase instance
        /// \param  aArg       [---;R--]  Name of the script
        /// \endcond
        /// \cond   fr
        /// \brief  Execute un fichier de commande
        /// \param  aToolBase  [---;RW-]  Une instance de ToolBase
        /// \param  aArg       [---;R--]  Nom du fichier de commandes
        /// \endcond
        static void ExecuteScript(ToolBase * aToolBase, const char * aArg);

        /// \cond   en
        /// \brief  Exit
        /// \param  aToolBase  [---;RW-]  A ToolBase instance
        /// \param  aArg       [---;R--]  The exit value
        /// \endcond
        /// \cond   fr
        /// \brief  Sortir
        /// \param  aToolBase  [---;RW-]  Une instance de ToolBase
        /// \param  aArg       [---;R--]  La valeur a retourner
        /// \endcond
        static void	Exit(ToolBase * aToolBase, const char * aArg);

    private:

        void ExecuteCommand(                                                 const char * aLine);
        void ExecuteCommand(const KmsLib::ToolBase::CommandInfo * aCommands, const char * aLine);

        void ParseCommands(FILE * aFile);

        const CommandInfo * mCommands;

    };

}
