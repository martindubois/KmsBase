
// Author / Auteur     KMS - Martin Dubois, ing.
// Product / Produit   KmsBase
// File / Fichier      KmsLib/IgnoreList.cpp

// todo   Supporter le \ pour escape des #
// todo   Supporter le \ pour escape des trailling space
// todo   Supporter le \ pour escape des !
// todo   Supporter le ! pour nier une exclusion
// todo   Supporter le **/
// todo   Supporter le /**
// todo   Supporter le /**/
// todo   Supporter les [] dans les pattern

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

static void ReplaceSlash(char * aLine);

static bool Trim(char * aLine);

namespace KmsLib
{

	// Public
	/////////////////////////////////////////////////////////////////////////

	IgnoreList::IgnoreList(IgnoreList * aParent, const char * aPrefix) : mParent(aParent)
	{
		if (NULL != aPrefix)
		{
			assert(NULL != aParent);

			mPrefix = aPrefix;
		}
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
			if ((!lIt->mFlags.mFolder) && Match((*lIt), aFileName))
			{
				return true;
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
			if (lIt->mFlags.mFolder && Match((*lIt), aFolderName))
			{
				return true;
			}
		}

		if (NULL != mParent)
		{
			return mParent->IsFolderIgnored(aFolderName);
		}

		return false;
	}

	void IgnoreList::ReadFromFile(const char * aFolderName, const char * aFileName)
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

		while (NULL != fgets(lLine, sizeof(lLine) / sizeof(lLine[0]), lFile))
		{
			lEntry.mFlags.mFolder	= Trim		(lLine)	;
			lEntry.mFlags.mPattern	= IsPatern	(lLine)	;

			switch (lLine[0])
			{
			case '#'	: // Comment / Commentaire
				break;

			case '\0'	: // Empty line / Ligne vide
				break;

			case '/'	: // Absolute entry / Entree absolue
				ReplaceSlash(lLine + 1);

				lEntry.mFlags.mAbsolute = true;
				lEntry.mString			= lLine + 1	;
				mList.push_back(lEntry);
				break;

			default		: // Relativ entry / Entree relative
				ReplaceSlash(lLine);

				lEntry.mFlags.mAbsolute = false;
				lEntry.mString			= lLine;
				mList.push_back(lEntry);
			}
		}

		lErrNo = fclose(lFile);
		assert(0 == lErrNo);
	}

	// Private
	/////////////////////////////////////////////////////////////////////////

	// aEntry		[---;R--]
	// aFileName	[---;R--]
	//
	// Return
	//	false
	//	true
	bool IgnoreList::Match(const Entry & aEntry, const char * aFileName) const
	{
		assert(NULL != (&aEntry));
		assert(NULL != aFileName);

		unsigned int lIndex = static_cast<unsigned int>(mPrefix.size());
		if (0 < lIndex)
		{
			if ((0 != strncmp(mPrefix.c_str(), aFileName, mPrefix.size())) || (SLASH_C != aFileName[lIndex]))
			{
				return false;
			}

			lIndex++;
		}

		bool lResult;

		const char * lPtr = aFileName + lIndex;

		// A sub folder may existe between the prefix and the relative entry.
		// The loop skip 0..n folder name and try. / Un nom de repertoire
		// peut exister entre le prefix et l'entree relative. La boucle saute
		// 0..n nom de repertoire et essaie.
		for ( ;; )
		{
			lResult = MatchNameOrPattern(aEntry, lPtr);

			if (aEntry.mFlags.mAbsolute || lResult)
			{
				break;
			}

			lPtr = strchr(lPtr, SLASH_C);
			if (NULL == lPtr)
			{
				break;
			}

			lPtr++;
		}

		return lResult;
	}

	// aEntry		[---;R--]	List entry / Entree de la liste
	// aFileName	[---;R--]	File or folder name / Nom de fichier ou de
	//							dossier
	//
	// Return / Retour
	//	false
	//	true
	bool IgnoreList::MatchNameOrPattern(const Entry & aEntry, const char * aFileName) const
	{
		assert(NULL != (&aEntry));
		assert(NULL != aFileName);

		bool lResult;

		if (aEntry.mFlags.mPattern)
		{
			lResult = MatchPatern	(aEntry.mString.c_str(), aFileName);
		}
		else
		{
			lResult = MatchName		(aEntry.mString.c_str(), aFileName);
		}

		return lResult;
	}

}

// Fonctions statiques
/////////////////////////////////////////////////////////////////////////////

// aPatern	[---;R--]	A pattern or a filename / Un modele ou un nom de
//						fichier
//
// Return / Retour
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

// aName    [---;R--]	Name to ignore / Nom a ignorer
// aToMatch	[---;R--]	File or folder name / Nom du fichier ou du dossier
//
// Return / Retour
//	false
//	true
bool MatchName(const char * aName, const char * aToMatch)
{
	assert(NULL != aName	);
	assert(NULL != aToMatch	);

	return (0 == strcmp(aName, aToMatch));
}

// aPatern	[---;R--]	Pattern to ignore / Modele a ignorer
// aToMatch	[---;R--]	File or folder name / Nom du fichier ou du dossier
//
// Return / Retour
//     false
//     true
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

// aLine	[---;RW-]	Replace the '/' with SLASH_C / Remplacer les '/' par
//						SLASH_C
void ReplaceSlash(char * aLine)
{
	assert(NULL != aLine);

#if ( '/' != SLASH_C )

	char * lPtr = aLine;

	while ('\0' != (*lPtr))
	{
		if ('/' == (*lPtr))
		{
			(*lPtr) = SLASH_C;
		}

		lPtr++;
	}

#endif

}

// aLine	[---;RW-]
//
// Return / Retour
//  false = It's a file name / C'est un nom de fichier
//  true  = It's a folder name / C'est un nom de dossier
bool Trim(char * aLine)
{
	assert(NULL != aLine);

	size_t i = strlen(aLine);
	while (0 < i)
	{
		i--;

		switch (aLine[i])
		{
		case '/'	:
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
