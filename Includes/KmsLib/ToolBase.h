
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	Includes/KmsLib/ToolBase.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== KmsBase =============================================================
#include <KmsLib/Exception.h>

namespace KmsLib
{

	// Class / Classe
	/////////////////////////////////////////////////////////////////////////

	// TODO :	AskUser - En faire des method non statique. Si le aFile est
	//			NULL, utiliser le fichier d'entree courrant.

	class ToolBase
	{

	public:

		typedef enum
		{
			REPORT_ERROR		,
			REPORT_FATAL_ERROR	,
			REPORT_INFO			,
			REPORT_OK			,
			REPORT_USER_ERROR	,
			REPORT_WARNING		,

			REPORT_QTY
		}
		ReportType;

		typedef void (*Function)(ToolBase * aToolBase, const char * aArg);

		typedef struct CommandInfo
		{
			const char				  * mName		;
			Function					mFunction	;
			const char			 	  * mHelpLine	;
			const struct CommandInfo  * mSubCommands;
		}
		CommandInfo;

		static void AskUser					(FILE * aFile, const char * aName, unsigned short aMin, unsigned short aMax, unsigned short aDefault, unsigned short * aOut);
		static void AskUser					(FILE * aFile, const char * aName,							char * aOut, unsigned int aOutSize_byte);
		static void AskUser					(FILE * aFile, const char * aName, const char * aDefault,	char * aOut, unsigned int aOutSize_byte);
		static void AskUser_InputFileName	(FILE * aFile, const char * aName,							char * aOut, unsigned int aOutSize_byte);
		static void AskUser_OutputFileName	(FILE * aFile, const char * aName, const char * aDefault,	char * aOut, unsigned int aOutSize_byte);

		static void Report(ReportType aType);
		static void Report(ReportType aType, const KmsLib::Exception * aException);
		static void Report(ReportType aType, const char * aMessage);

		ToolBase(const CommandInfo * aCommands);

		bool	ParseArguments(int aCount, const char ** aVector);

		void	ParseCommands();
		void	ParseCommands(const char * aFileName);

		// ===== Function ===================================================

		static void ExecuteScript	(ToolBase * aToolBase, const char * aArg);
		static void	Exit			(ToolBase * aToolBase, const char * aArg);

	private:

		void	ExecuteCommand(													const char * aLine);
		void	ExecuteCommand(const KmsLib::ToolBase::CommandInfo * aCommands,	const char * aLine);

		void	ParseCommands(FILE * aFile);

		const CommandInfo * mCommands;

	};

}