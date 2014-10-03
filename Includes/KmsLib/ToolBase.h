
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	Includes/KmsLib/ToolBase.h

#pragma once

namespace KmsLib
{

	// Class
	/////////////////////////////////////////////////////////////////////////

	class ToolBase
	{

	public:

		typedef void (*Function)(ToolBase * aToolBase, const char * aArg);

		typedef struct CommandInfo
		{
			const char				  * mName		;
			Function					mFunction	;
			const char			 	  * mHelpLine	;
			const struct CommandInfo  * mSubCommands;
		}
		CommandInfo;

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