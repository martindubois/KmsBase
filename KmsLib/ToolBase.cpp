
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib/ToolBase.cpp

// TODO : 	Ajouter une fonction predefinie pour repeter une commande un
//		certain nombre de fois.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>

#include <KmsLib/ToolBase.h>

// Constants / Constantes
/////////////////////////////////////////////////////////////////////////////

#define LINE_LENGTH_MAX	(1024)

// Static function declarations / Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static void	DisplayHelp		(const KmsLib::ToolBase::CommandInfo * aCommandInfo);

static void ReadLine		(FILE * aFile, char * aOut, unsigned int aOutsize_byte);

namespace KmsLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	// aFile	: [in,out]	Input stream / Fichier d'entree
	// aName	: [in]		Name of the requested information / Nom de
	//						l'information a obtenir
	// aMin		:			Minmal value / Valeur minimale
	// aMax		:			Maximal value / Valeur maximale
	// aDefault	:			Default value / Valeur par defaut
	// aOut		: [   out]	Output buffer / Emplacement de sortie
	//
	// Exception :	KmsLib::Exception	CODE_IO_ERROR
	void ToolBase::AskUser(FILE * aFile, const char * aName, unsigned short aMin, unsigned short aMax, unsigned short aDefault, unsigned short * aOut)
	{
		assert(NULL !=	aFile		);
		assert(NULL !=	aName		);
		assert(aMin <	aMax		);
		assert(aMin <=	aDefault	);
		assert(aMax >=	aDefault	);
		assert(NULL !=	aOut		);

		for (;;)
		{
			if (stdin == aFile)
			{
				// NOT TESTED :	The test program use the stdin / Le programme
				//				de test utilise l'entree standard
				printf("%s\t(Range: %u to %u;\tDefault: %u) : ", aName, aMin, aMax, aDefault);
			}

			char lLine[2048];

			ReadLine(aFile, lLine, sizeof(lLine));

			unsigned int lValue;

			int lRetI = sscanf_s(lLine, "%u", &lValue);
			switch ( lRetI )
			{
			case EOF:
				(*aOut) = aDefault;
				return;

			case 1 :
				if ((aMin <= lValue) && (aMax >= lValue))
				{
					(*aOut) = lValue;
					return;
				}

				// No break;

			default:
				Report(REPORT_USER_ERROR, "Invalid value, try again!");
				break;
			}
		}
	}

	// aFile	: [in,out]	Input stream / Fichier d'entree
	// aName	: [in]		Name of the requested information / Nom de
	//						l'information a obtenir
	// aOut		: [   out]	Output buffer / Emplacement de sortie
	//
	// Exception :	KmsLib::Exception	CODE_IO_ERROR
	void ToolBase::AskUser(FILE * aFile, const char * aName, char * aOut, unsigned int aOutSize_byte)
	{
		assert(NULL !=	aFile			);
		assert(NULL !=	aName			);
		assert(NULL !=	aOut			);
		assert(0	<	aOutSize_byte	);

		for (;;)
		{
			if (stdin == aFile)
			{
				// NOT TESTED :	The test program use the stdin / Le programme
				//				de test utilise l'entree standard
				printf("%s : ", aName);
			}

			char lLine[2048];

			ReadLine(aFile, lLine, sizeof(lLine));

			char lValue[2048];

			memset(&lValue, 0, sizeof(lValue));

			int lRetI = sscanf_s(lLine, "%[^\n\r\t]", lValue, sizeof(lValue) - 1);
			switch (lRetI)
			{
			case 1:
				size_t lLen;

				lLen = strlen(lValue);
				if (aOutSize_byte <= lLen)
				{
					Report(REPORT_USER_ERROR, "Too long, try again!");
					break;
				}

				// No break;

			default :
				strcpy_s(aOut, aOutSize_byte, lValue);
				return;
			}
		}
	}

	// aFile			: [in,out]	Input stream / Fichier d'entree
	// aName			: [in]		Name of the requested information / Nom
	//								de l'information a obtenir
	// aDefault			: [in]		Default value / Valeur par defaut
	// aOut				: [   out]	Output buffer / Emplacement de sortie
	// aOutSize_byte	:			Output buffer size / Taille de
	//								l'emplacement de sortie
	//
	// Exception :	KmsLib::Exception	CODE_IO_ERROR
	//									CODE_USER_ERROR
	void ToolBase::AskUser(FILE * aFile, const char * aName, const char * aDefault, char * aOut, unsigned int aOutSize_byte)
	{
		assert(NULL !=	aFile			);
		assert(NULL !=	aName			);
		assert(NULL !=	aDefault		);
		assert(NULL !=	aOut			);
		assert(0	<	aOutSize_byte	);

		for (;;)
		{
			if (stdin == aFile)
			{
				printf("%s\t(Default: \"%s\") : ", aName, aDefault);
			}

			char lLine[2048];

			ReadLine(aFile, lLine, sizeof(lLine));

			char lValue[2048];

			memset(&lValue, 0, sizeof(lValue));

			int lRetI = sscanf_s(lLine, "%[^\n\r\t]", lValue, sizeof(lValue) - 1);
			switch (lRetI)
			{
			case 1:
				size_t lLen;

				lLen = strlen(lValue);
				if (aOutSize_byte <= lLen)
				{
					Report(REPORT_USER_ERROR, "Too long, try again!");
					break;
				}

				strcpy_s(aOut, aOutSize_byte, lValue);
				return;

			default:
				strcpy_s(aOut, aOutSize_byte, lValue);
				return;
			}
		}
	}

	// aFile			: [in,out]	Input stream / Fichier d'entree
	// aName			: [in]		Name of the requested information / Nom
	//								de l'information a obtenir
	// aOut				: [   out]	Output buffer / Emplacement de sortie
	// aOutSize_byte	:			Output buffer size / Taille de
	//								l'emplacement de sortie
	//
	// Exception :	KmsLib::Exception	CODE_IO_ERROR
	//									CODE_USER_ERROR
	void ToolBase::AskUser_InputFileName(FILE * aFile, const char * aName, char * aOut, unsigned int aOutSize_byte)
	{
		assert(NULL !=	aFile			);
		assert(NULL !=	aName			);
		assert(NULL !=	aOut			);
		assert(0	<	aOutSize_byte	);

		for (;;)
		{
			AskUser(aFile, aName, aOut, aOutSize_byte);

			if (0 == _access(aOut, 4))
			{
				break;
			}

			Report(REPORT_USER_ERROR, "The file does not exist, try again!");
		}
	}

	// aFile			: [in,out]	Input stream / Fichier d'entree
	// aName			: [in    ]	Name of the requested information / Nom
	//								de l'information a obtenir
	// aDefault			: [in    ]  Default file name / Nom de fichier par
	//								defaut
	// aOut				: [   out]	Output buffer / Emplacement de sortie
	// aOutSize_byte	:			Output buffer size / Taille de
	//								l'emplacement de sortie
	//
	// Exception :	KmsLib::Exception	CODE_IO_ERROR
	//									CODE_USER_ERROR
	void ToolBase::AskUser_OutputFileName(FILE * aFile, const char * aName, const char * aDefault, char * aOut, unsigned int aOutSize_byte)
	{
		assert(NULL !=	aFile			);
		assert(NULL !=	aName			);
		assert(NULL !=	aDefault		);
		assert(NULL !=	aOut			);
		assert(0	<	aOutSize_byte	);

		for (;;)
		{
			AskUser(aFile, aName, aDefault, aOut, aOutSize_byte);

			if (0 != _access(aOut, 0))
			{
				break;
			}

			Report(REPORT_USER_ERROR, "The file already exists, try again!");
		}
	}

	// aType	:	See / Voir REPORT_...
	void ToolBase::Report(ReportType aType)
	{
		const char * lTypeName = NULL;
		// Initialized in order to avoir the compilation warning / Initialise
		// pour eviter le message a la compilation

		switch (aType)
		{
		case REPORT_ERROR		: lTypeName = "ERROR"		; break;
		case REPORT_FATAL_ERROR	: lTypeName = "FATAL ERROR"	; break;
		case REPORT_INFO		: lTypeName = "INFO"		; break;
		case REPORT_OK			: lTypeName = "OK"			; break;
		case REPORT_USER_ERROR	: lTypeName = "USER ERROR"	; break;
		case REPORT_WARNING		: lTypeName = "WARNING"		; break;

		default: assert(false);
		}

		printf("\n%s : ", lTypeName);
	}

	// aType		:	See / Voir REPORT_...
	// aException	:	Exception to report / L'exception a rapporter
	void ToolBase::Report(ReportType aType, const KmsLib::Exception * aException)
	{
		assert(NULL != aException);

		Report(aType);

		printf("Exception\n");

		aException->Write(stdout);
	}

	// aType	:		See / Voir REPORT_...
	// aMessage	: [in]	Message
	void ToolBase::Report(ReportType aType, const char * aMessage)
	{
		assert(NULL != aMessage);

		Report(aType);

		printf("%s\n", aMessage);
	}

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

		int lRet = sscanf_s(aLine, "%[0-1A-Za-z] %[^\n\r\t]", lName, LINE_LENGTH_MAX, lArguments, LINE_LENGTH_MAX);
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
				else
				{
					Report(REPORT_USER_ERROR);
					printf("Invalid command (%s)\n", lName);
				}
			}

			break;

		default:
			Report(REPORT_USER_ERROR);
			printf("Invalid command line (%s)\n", aLine);
		}
	}

	// aFile	: [in,out]
	void ToolBase::ParseCommands(FILE * aFile)
	{
		assert(NULL != aFile);

		for (;;)
		{
			if (stdin == aFile)
			{
				printf("\n> ");
			}

			char lLine[LINE_LENGTH_MAX];

			memset(&lLine, 0, sizeof(lLine));

			if (NULL == fgets(lLine, LINE_LENGTH_MAX - 1, aFile))
			{
				break;
			}

			size_t lLen = strlen(lLine);
			if ((0 < lLen) && ('#' != lLine[0]))
			{
				while (0 < lLen)
				{
					lLen--;
					switch (lLine[lLen])
					{
					case '\0' :
						assert(false);

					case ' '	:
					case '\n'	:
					case '\r'	:
					case '\t'	:
						lLine[lLen] = '\0';
						break;

					default:
						ExecuteCommand(lLine);
						lLen = 0;
					}
				}
			}
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
			Report(REPORT_USER_ERROR);
			printf("The filename is not valid (%s)\n", aFileName);
			break;

		default:
			FILE * lFile;

			int lRet = fopen_s(&lFile, aFileName, "r");
			if (0 == lRet)
			{
				Report(REPORT_INFO);
				printf("Executing commands from file %s ...\n", aFileName);

				ParseCommands(lFile);

				Report(REPORT_INFO);
				printf("End of file %s\n", aFileName);
			}
			else
			{
				Report(REPORT_ERROR);
				printf("Cannot open file %s\n", aFileName);
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

// aFile			: [in,out]	Input stream / Fichier d'entree
// aOut				: [   out]	Output buffer / Espace de sortie
// aOutSize_byte	:			Output buffe size / Taille de l'espace de
//								sortie
//
// Exception :	KmsLib::Exception	CODE_IO_ERROR
void ReadLine(FILE * aFile, char * aOut, unsigned int aOutSize_byte)
{
	memset(aOut, 0, aOutSize_byte);

	if (NULL == fgets(aOut, aOutSize_byte - 1, aFile))
	{
		throw new KmsLib::Exception(KmsLib::Exception::CODE_IO_ERROR, "fgets( , ,  ) failed", NULL, __FILE__, __FUNCTION__, __LINE__, aOutSize_byte);
	}
}
