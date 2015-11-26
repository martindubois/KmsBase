
// Author / Auteur		:	KMS -	Martin Dubois, ing.
// Product / Produit	:	KmsBase
// File / Fichier		:	KmsLib/IgnoreList.cpp

// Inclusions
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== C ==================================================================
#include <assert.h>
#include <stdlib.h>

// ===== KmsLib =============================================================
#include <KmsLib/Exception.h>

#include <KmsLib/IgnoreList.h>

// Declaration des fonctions statiques
/////////////////////////////////////////////////////////////////////////////

static bool IsPatern(const char * aLine);

static bool MatchName  (const char * aName  , const char * aToMatch);
static bool MatchPatern(const char * aPatern, const char * aToMatch);

static bool Trim(char * aLine);

namespace KmsLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	IgnoreList::IgnoreList(IgnoreList * aParent) : mParent(aParent)
	{
	}

	IgnoreList * IgnoreList::GetParent()
	{
		return mParent;
	}

	bool IgnoreList::IsFileIgnored(const char * aFileName) const
	{
		assert(NULL != aFileName);

		for (EntryList::const_iterator lIt = mList.begin(); lIt != mList.end(); lIt++)
		{
			if (!lIt->mFolder)
			{
				if (lIt->mPattern)
				{
					if (MatchPatern(lIt->mString.c_str(), aFileName))
					{
						return true;
					}
				}
				else
				{
					if (MatchName(lIt->mString.c_str(), aFileName))
					{
						return true;
					}
				}
			}
		}

		if (NULL != mParent)
		{
			return mParent->IsFileIgnored(aFileName);
		}

		return false;
	}

	bool IgnoreList::IsFolderIgnored(const char * aFolderName) const
	{
		assert(NULL != aFolderName);

		for (EntryList::const_iterator lIt = mList.begin(); lIt != mList.end(); lIt++)
		{
			if (lIt->mFolder)
			{
				if (lIt->mPattern)
				{
					if (MatchPatern(lIt->mString.c_str(), aFolderName))
					{
						return true;
					}
				}
				else
				{
					if (MatchName(lIt->mString.c_str(), aFolderName))
					{
						return true;
					}
				}
			}
		}

		if (NULL != mParent)
		{
			return mParent->IsFolderIgnored(aFolderName);
		}

		return false;
	}

	void IgnoreList::ReadFromFile(const char * aFolderName, const char * aPrefix, const char * aFileName)
	{
		assert(NULL != aFolderName	);
		assert(NULL != aFileName	);

		char lFileName[2048];

		sprintf_s(lFileName, "%s" SLASH "%s", aFolderName, aFileName);

		FILE * lFile;

		errno_t lErrNo = fopen_s(&lFile, lFileName, "r");
		if (0 != lErrNo)
		{
			char lMessage[2048];

			sprintf_s(lMessage, "fopen_s( , %s,  ) failed", lFileName);

			throw new KmsLib::Exception(KmsLib::Exception::CODE_IO_ERROR,
				"fopen_s( , ,  ) failed", lMessage, __FILE__, __FUNCTION__, __LINE__, lErrNo);
		}

		assert(NULL != lFile);

		Entry lEntry;

		char lLine[2048];
		char lTemp[2048];

		while (NULL != fgets(lLine, sizeof(lLine) / sizeof(lLine[0]), lFile))
		{
			lEntry.mFolder	= Trim		(lLine);
			lEntry.mPattern	= IsPatern	(lLine);

			switch (lLine[0])
			{
			case '#':
				// Commentaire
				break;

			case '\0':
				// Ligne vide
				break;

			case '/':
				// NOT TESTED
				// TODO	Test
				if (NULL == aPrefix)
				{
					sprintf_s(lTemp, "%s", lLine + 1);
				}
				else
				{
					sprintf_s(lTemp, "%s" SLASH "%s", aPrefix, lLine + 1);
				}

				lEntry.mString = lTemp;
				mList.push_back(lEntry);
				break;

			default:
				if (NULL == aPrefix)
				{
					sprintf_s(lTemp, "%s", lLine);
				}
				else
				{
					sprintf_s(lTemp, "%s" SLASH "%s", aPrefix, lLine);
				}

				lEntry.mString = lTemp;
				mList.push_back(lEntry);
			}
		}

		lErrNo = fclose(lFile);
		assert(0 == lErrNo);
	}
}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// aPatern : [in]
//
// Retour :
//  false
//  true
bool IsPatern(const char * aPatern)
{
	assert(NULL != aPatern);

	if (NULL != strchr(aPatern, '*'))
	{
		return true;
	}

	if (NULL != strchr(aPatern, '?'))
	{
		return true;
	}

	return false;
}

// aName    : [in] Nom a ignorer
// aToMatch : [in] Nom du fichier ou du dossier
//
// Retour :
//     false = Pas de correspondance
//     true  = Correspondance
bool MatchName(const char * aName, const char * aToMatch)
{
	assert(NULL != aName	);
	assert(NULL != aToMatch	);

	return (0 == strcmp(aName, aToMatch));
}

// aPatern  : [in] Patron a ignorer
// aToMatch : [in] Nom du fichier ou du dossier
//
// Retour :
//     false = Pas de correspondance
//     true  = Correspondance
bool MatchPatern(const char * aPatern, const char * aToMatch)
{
	assert(NULL != aPatern	);
	assert(NULL != aToMatch	);

	for (;;)
	{
		switch (*aPatern)
		{
		case '\0' :
			return ('\0' == ( * aToMatch ) );

		case '?' :
			if ('\0' == (*aToMatch))
			{
				return false;
			}

			aPatern		++;
			aToMatch	++;
			break;

		case '*' :
			if ('\0' == (*aToMatch))
			{
				aPatern ++;
			}
			else
			{
				if (MatchPatern(aPatern + 1, aToMatch))
				{
					return true;
				}

				aToMatch++;
			}
			break;

		default :
			if ( ( * aPatern ) != ( * aToMatch ) )
			{
				return false;
			}

			aPatern		++;
			aToMatch	++;
		}
	}

	// NOT TESTED :	This return statement is there to avoid the warning / Ce
	//				return est seulement la pour eviter le warning.
	return false;
}

// aLine : [in,out]
//
// Retour :
//  false = C'est un nom de fichier
//  true  = C'est un nom de dossier
bool Trim(char * aLine)
{
	assert(NULL != aLine);

	size_t i = strlen(aLine);
	while (0 < i)
	{
		i--;

		switch (aLine[i])
		{
		case '/' :
			aLine[i] = '\0';
			return true;

		case '\n' :
		case '\r' :
		case '\t' :
		case ' ' :
			aLine[i] = '\0';
			break;

		default :
			return false;
		}
	}

	return false;
}
