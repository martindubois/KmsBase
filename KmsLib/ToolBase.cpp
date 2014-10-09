
// Auteur	:	KMS -	Martin Dubois, ing.
// Projet	:	KmsBase
// Fichier	:	KmsLib/ToolBase.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>
#include <string.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/ToolBase.h>

// Constantes
/////////////////////////////////////////////////////////////////////////////

#define LINE_LENGTH_MAX	(1024)

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void	DisplayHelp		(const KmsLib::ToolBase::CommandInfo * aCommandInfo);

namespace KmsLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	// aCommands	: [in,keep]
	ToolBase::ToolBase(const CommandInfo * aCommands) : mCommands(aCommands)
	{
		assert(NULL != mCommands);
	}

	// aCount	:
	// aVector	: [in]
	//
	// Return :
	//  false	= La method n'a pas executer de commande
	//  true	= La method a executer au moins une commande
	//
	// Exception : KmsLib::Exception
	bool ToolBase::ParseArguments(int aCount, const char ** aVector)
	{
		size_t lLen;

		switch (aCount)
		{
		case 1 :
			break;

		case 3 :
			lLen = strlen(aVector[1]);

			if (0 == _strnicmp("Command", aVector[1], lLen))
			{
				ExecuteCommand(aVector[2]);
				return true;
			}

			if (0 == _strnicmp("File", aVector[1], lLen))
			{
				ParseCommands(aVector[2]);
				return true;
			}

			// No break;

		default :
			throw new Exception(Exception::CODE_USER_ERROR, "Invalid command line", NULL, __FILE__, __FUNCTION__, __LINE__, aCount);
		}

		return false;
	}

	// Exception : KmsLib::Exception
	void ToolBase::ParseCommands()
	{
		// NOT TESTED : Conflit avec le stdin du program de test!
		ParseCommands(stdin);
	}

	// ===== Function =======================================================

	void ToolBase::ExecuteScript(ToolBase * aThis, const char * aArguments)
	{
		assert(NULL != aThis);
		assert(NULL != aArguments);

		aThis->ParseCommands(aArguments);
	}

	void ToolBase::Exit(ToolBase * aThis, const char * aArguments)
	{
		// NOT TESTED : Il ne faut pas quitter le programme de test!
		assert(NULL != aThis);
		assert(NULL != aArguments);

		exit(atoi(aArguments));
	}

	// Private
	/////////////////////////////////////////////////////////////////////////

	// aLine	: [in]
	void ToolBase::ExecuteCommand(const char * aLine)
	{
		assert(NULL != aLine);

		ExecuteCommand(mCommands, aLine);
	}

	// aCommandInfo	: [in]
	// aCommand		: [in]
	void ToolBase::ExecuteCommand(const KmsLib::ToolBase::CommandInfo * aCommands, const char * aLine)
	{
		assert(NULL != aCommands	);
		assert(NULL != aLine		);

		char lName		[LINE_LENGTH_MAX];
		char lArguments	[LINE_LENGTH_MAX];

		bool	lFound	;
		size_t	lLen	;

		int lRet = sscanf_s(aLine, "%[0-1A-Za-z] %[^\n\t]", lName, LINE_LENGTH_MAX, lArguments, LINE_LENGTH_MAX);
		switch (lRet)
		{
		case 1:
			memset(&lArguments, 0, sizeof(lArguments));

			// No break

		case 2:
			lLen = strlen(lName);

			for (unsigned int i = 0;; i++)
			{
				if (NULL == aCommands[i].mName)
				{
					lFound = false;
					break;
				}

				assert((NULL != aCommands[i].mFunction) || (NULL != aCommands[i].mSubCommands));
				assert((NULL == aCommands[i].mFunction) || (NULL == aCommands[i].mSubCommands));

				if (0 == _strnicmp(aCommands[i].mName, lName, lLen))
				{
					if (NULL != aCommands[i].mFunction)
					{
						aCommands[i].mFunction(this,lArguments);
					}
					else
					{
						ExecuteCommand(aCommands[i].mSubCommands, lArguments);
					}

					lFound = true;
					break;
				}
			}

			if (!lFound)
			{
				if (0 == _strnicmp("Help", lName, lLen))
				{
					DisplayHelp(aCommands);
				}
			}

			break;

		default:
			printf("\nERROR : Invalid command line (%s)\n", aLine);
		}
	}

	// aFile	: [in,out]
	void ToolBase::ParseCommands(FILE * aFile)
	{
		assert(NULL != aFile);

		for ( ;; )
		{
			printf("\n> ");

			char lLine[LINE_LENGTH_MAX];

			if (NULL == fgets(lLine, LINE_LENGTH_MAX - 1, aFile))
			{
				break;
			}

			ExecuteCommand(lLine);
		}
	}

	// aFileName	: [in]
	void ToolBase::ParseCommands(const char * aFileName)
	{
		assert(NULL != aFileName);

		switch (aFileName[0])
		{
		case '\0' :
		case '\n' :
		case '\r' :
		case '\t' :
			printf("\nERROR : Le filename is not valid (%s)\n", aFileName);
			break;

		default:
			FILE * lFile;

			int lRet = fopen_s(&lFile, aFileName, "r");
			if (0 == lRet)
			{
				printf("\nExecuting commands from file %s ...\n", aFileName);

				ParseCommands(lFile);

				printf("\nEnd of file %s\n", aFileName);
			}
			else
			{
				printf("\nERROR : Cannot open file %s\n", aFileName);
			}
		}
	}

};

// Fonction statique
/////////////////////////////////////////////////////////////////////////////

// aCommandInfo	: [in]
void DisplayHelp(const KmsLib::ToolBase::CommandInfo * aCommandInfo)
{
	assert(NULL != aCommandInfo);

	printf("\n");

	for (unsigned int i = 0;; i++)
	{
		if (NULL == aCommandInfo[i].mName)
		{
			break;
		}

		printf("%s\n", aCommandInfo[i].mHelpLine);
	}

	printf("Help                          Display this help message\n");
}
