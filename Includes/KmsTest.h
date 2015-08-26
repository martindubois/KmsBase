
// Product / Produit	:	KmsBase

/// \author	KMS - Martin Dubois, ing.
/// \file	Includes/KmsTest.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== C ==================================================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ===== C++ ================================================================
#include <exception>

// Constants
/////////////////////////////////////////////////////////////////////////////

/// \cond en
/// \brief  This flag indicates the test require user interaction.
/// \endcond
/// \cond fr
/// \brief	Ce drapeau indique que le test necessite une interaction avec
///			l'utilisateur.
/// \endcond
#define KMS_TEST_FLAG_INTERACTION_NEEDED	(0x00000001)

// Type de donnees
/////////////////////////////////////////////////////////////////////////////

/// \cond en
/// \brief  Definition of the type of a test function
/// \endcond
/// \cond fr
/// \brief	Definition du type d'une fonction de test
/// \endcond
typedef int(*KmsTestFunction)(void);

/// \cond

typedef struct
{
	unsigned int	mFlags		;
	KmsTestFunction	mFunction	;
	unsigned int	mGroup		;
	const char	  * mName		;
}
KmsTestDescription;

/// \endcond

// Macro
/////////////////////////////////////////////////////////////////////////////

// ===== Test ===============================================================

/// \cond	en
/// \brief  This macro fail the test if the condition \a Co is false.
/// \endcond
/// \cond	fr
/// \brief	Cette macro echoue le test si la condition \a Co est fausse.
/// \endcond	
#define KMS_TEST_ASSERT(Co)																	\
	if (!(Co))																				\
	{																						\
		printf("Test " __FUNCTION__ " failed at line %u of file " __FILE__ "\n", __LINE__);	\
		return 1;																			\
	}

/// \cond	en
/// \brief	If the condition \a Co is false, this macro fail the test and
///			continue the execution at \a Cl label for cleanup.
/// \endcond
/// \cond	fr
/// \brief	Si la condition \a Co est fausse, cette macro echoue le test et
///			continue l'execution a l'ettiquette \a Cl pour le nettoyage.
/// \endcond
#define KMS_TEST_ASSERT_CLEANUP(Co,Cl)														\
	if (!(Co))																				\
	{																						\
		printf("Test " __FUNCTION__ " failed at line %u of file " __FILE__ "\n", __LINE__);	\
		goto Cl;																			\
	}

/// \cond	en
/// \brief	This macro indicates the begining of the test named \a Na.
/// \endcond
/// \cond	fr
/// \brief	Cette macro indique le debut du test nomme \a Na.
/// \endcond
#define KMS_TEST_BEGIN(Na)			\
	int Na()						\
	{								\
		unsigned int lResult = 0;	\
		try							\
		{

/// \cond	en
/// \brief	This macro indicate the end of the test.
/// \endcond
/// \cond	fr
/// \brief	Cette macro indique la fin du test.
/// \endcond
#define KMS_TEST_END				\
		}							\
		catch (std::exception * eE)	\
		{							\
			printf("Test " __FUNCTION__ " failed at line %u of file " __FILE__ " (std::exception - %s)\n", __LINE__, eE->what());	\
			return 1;				\
		}							\
		catch ( ... )				\
		{							\
			printf("Test " __FUNCTION__ " failed at line %u of file " __FILE__ " (Unknown exception)\n", __LINE__);	\
			return 1;				\
		}							\
		return lResult;				\
	}

/// \cond	en
/// \brief	As KMS_TEST_END but display KmsLib::Exception.
/// \note	If a test program use this macro, it must link with KmsLib.lib.
/// \endcond
/// \cond	fr
/// \brief	Comme KMS_TEST_END, mais affiche les KmsLib::Exception.
/// \note	Si un programme de test utilise cette macro, KmsLib.lib doit etre
///			inclue lors de l'edition des liens.
/// \endcond
#define KMS_TEST_END_2					\
		}								\
		catch (KmsLib::Exception * eE)	\
		{								\
			printf("Test " __FUNCTION__ " failed at line %u of file " __FILE__ " (KmsLib::Exception)\n", __LINE__);	\
			eE->Write(stdout);			\
			return 1;					\
		}								\
		catch (std::exception * eE)		\
		{								\
			printf("Test " __FUNCTION__ " failed at line %u of file " __FILE__ " (std::exception - %s)\n", __LINE__, eE->what());	\
			return 1;					\
		}								\
		catch (...)						\
		{								\
			printf("Test " __FUNCTION__ " failed at line %u of file " __FILE__ " (Unknown exception)\n", __LINE__);	\
			return 1;					\
		}								\
	return lResult;						\
	}

/// \cond	en
/// \brief	This macro display a message indicating the following error
///			message is caused by a test of error handling code.
/// \endcond
/// \cond	fr
/// \brief	Cette macro affiche un message qui indique que le message
//			d'erreur qui suit est du a un test du code de gestion d'erreur.
/// \endcond
#define KMS_TEST_ERROR_INFO	\
	printf("    ===== Information about a succesfully tested error condition =====\n")

// ===== Test group list ====================================================

/// \cond	en
/// \brief	This macro indicate the begining of the test group list.
/// \endcond
/// \cond	fr
/// \brief	Cette macro indique le debut de la liste de groupes de tests.
/// \endcond
#define KMS_TEST_GROUP_LIST_BEGIN					\
	static const char * KMS_TEST_GROUP_NAMES[] =	\
{

/// \cond	en
/// \brief	This macro indicate the end of the test group list.
/// \endcond
/// \cond	fr
/// \brief	Cette macro indique la fin de la liste de groupes de tests.
/// \endcond
#define KMS_TEST_GROUP_LIST_END	\
};

/// \cond	en
/// \brief	This macro add a test group to the test group list.
/// \endcond
/// \cond	fr
/// \brief	Cette macro ajoute un groupe a la liste des groupes de tests.
/// \endcond
#define KMS_TEST_GROUP_LIST_ENTRY(Na)	\
	Na,

// ===== Test list ==========================================================

/// \cond	en
/// \brief	This macro indicate the begining of the test list.
/// \endcond
/// \cond	fr
/// \brief	Cette macro indique le debut de la liste de tests.
/// \endcond
#define	KMS_TEST_LIST_BEGIN					\
	static KmsTestDescription KMS_TESTS[] = \
{

/// \cond	en
/// \brief	This macro indicate the end of the test list.
/// \endcond
/// \cond	fr
/// \brief	Cette macro indique la fin de la liste de tests.
/// \endcond
#define KMS_TEST_LIST_END	\
};

/// \cond	en
/// \brief	This macro add a test to the test list.
/// \endcond
/// \cond	fr
/// \brief	Cette macro ajoute un test a la liste de tests.
/// \endcond
#define KMS_TEST_LIST_ENTRY(Fu,Na,Gr,Fl)	\
{ Fl, Fu, Gr, Na },

// ===== Main ===============================================================

/// \cond	en
/// \brief	This macro define the test executable entry point.
/// \endcond
/// \cond	fr
/// \brief  Cet macro definit le point d'entre d'un executable de test.
/// \endcond
#define KMS_TEST_MAIN														\
	static void	DisplayHelp(const char * aExe);								\
	static void	DisplayTests();												\
	static void	DisplayResults(int aResult);								\
	static int	RunAll();													\
	static int	RunAuto();													\
	static int	RunGroup(const char * aGroup);								\
	static int	RunTest(unsigned int aTest);								\
	static int	RunTests(const char ** aTests, int aCount);					\
																			\
	int main(int aCount, const char ** aVector)								\
	{																		\
		printf("Test program compiler at " __TIME__ " on " __DATE__ "\n\n");	\
																			\
		if ((1 >= aCount) || (0 == _stricmp("auto", aVector[1])))			\
		{																	\
			if (2 < aCount) { DisplayHelp(aVector[0]); return 1000; }		\
																			\
			return RunAuto();												\
		}																	\
																			\
		if (0 == _stricmp("all", aVector[1]))								\
		{																	\
			if (2 != aCount) { DisplayHelp(aVector[0]); return 1001; }		\
																			\
			return RunAll();												\
		}																	\
																			\
		if (0 == _stricmp("group", aVector[1]))								\
		{																	\
			if (3 != aCount) { DisplayHelp(aVector[0]);	return 1002; }		\
																			\
			return RunGroup(aVector[2]);									\
		}																	\
																			\
		if (0 == _stricmp("help", aVector[1]))								\
		{																	\
			DisplayHelp(aVector[0]);										\
			return ((2 == aCount) ? 0 : 1003);								\
		}																	\
																			\
		if (0 == _stricmp("list", aVector[1]))								\
		{																	\
			if (2 != aCount) { DisplayHelp(aVector[0]); return 1003; }		\
																			\
			DisplayTests();													\
			return 0;														\
		}																	\
																			\
		return RunTests( aVector + 1, aCount - 1);							\
	}																		\
																			\
	void DisplayHelp(const char * aExe)										\
	{																		\
		printf(																\
			"Usage:\n"														\
			"    %s\n"														\
			"	 %s all\n"													\
			"    %s auto\n"													\
			"    %s group {GroupNumber}\n"									\
			"    %s help\n"													\
			"    %s list\n"													\
			"    %s {TestNumber} [TestNumber] ...\n"						\
			"\n",															\
			aExe, aExe, aExe, aExe, aExe, aExe, aExe );						\
	}																		\
																			\
	void DisplayResults(int aResult)										\
	{																		\
		switch (aResult)													\
		{																	\
		case 0	: printf("\nAll tests PASSED\n\n"			); break;		\
		case 1	: printf("\n1 test FAILED\n\n"				); break;		\
		default	: printf("\n%u tests FAILED\n\n", aResult	); break;		\
		}																	\
	}																		\
																			\
	void DisplayTests()														\
	{																		\
		unsigned int i;														\
		printf("Groups:\n");												\
		printf("    #      Name\n");										\
		for (i = 0; i < (sizeof(KMS_TEST_GROUP_NAMES) / sizeof(KMS_TEST_GROUP_NAMES[0])); i++)	\
		{																	\
			printf("    %2u    %s\n", i, KMS_TEST_GROUP_NAMES[i]);			\
		}																	\
		printf( "\n" );														\
		printf("Tests\n");													\
		printf("    #     Group		Name\n");								\
		for (i = 0; i < (sizeof(KMS_TESTS) / sizeof(KMS_TESTS[0])); i++)	\
		{																	\
			printf("    %2u    %2u        %s", i, KMS_TESTS[i].mGroup, KMS_TESTS[i].mName);	\
			if (0 != (KMS_TEST_FLAG_INTERACTION_NEEDED & KMS_TESTS[i].mFlags))	\
			{																\
				printf("\t- Interaction needed");							\
			}																\
			printf("\n");													\
		}																	\
		printf("\n");														\
	}																		\
																			\
	int RunAll()															\
	{																		\
		printf("Executing all tests...\n\n");								\
		int lResult = 0;													\
																			\
		for (unsigned int i = 0; i < (sizeof(KMS_TESTS) / sizeof(KMS_TESTS[0])); i++)	\
		{																	\
			lResult += RunTest(i);											\
		}																	\
																			\
		DisplayResults(lResult);											\
		return lResult;														\
	}																		\
																			\
	int RunAuto()															\
	{																		\
		printf("Executing all tests that doesn't require interaction...\n\n");	\
		int lResult = 0;													\
																			\
		for (unsigned int i = 0; i < (sizeof(KMS_TESTS) / sizeof(KMS_TESTS[0])); i++)	\
		{																	\
			if (0 == (KMS_TESTS[i].mFlags & KMS_TEST_FLAG_INTERACTION_NEEDED))	\
			{																\
				lResult += RunTest(i);										\
			}																\
		}																	\
																			\
		DisplayResults(lResult);											\
		return lResult;														\
	}																		\
																			\
	int RunGroup(const char * aGroupNumber)									\
	{																		\
		unsigned int lGroup	= strtoul(aGroupNumber, NULL, 10);				\
																			\
		printf("Executing test group %u ...\n\n", lGroup);					\
		int	lResult = 0;													\
																			\
		for (unsigned int i = 0; i < (sizeof(KMS_TESTS) / sizeof(KMS_TESTS[0])); i++)	\
		{																	\
			if (lGroup == KMS_TESTS[i].mGroup)								\
			{																\
				lResult += RunTest(i);										\
			}																\
		}																	\
																			\
		DisplayResults(lResult);											\
		return lResult;														\
	}																		\
																			\
	int RunTest(unsigned int aTest)											\
	{																		\
		printf("Executing test %u : %s\n", aTest, KMS_TESTS[aTest].mName);		\
		int lResult = KMS_TESTS[aTest].mFunction();							\
		printf("Test %u : %s\n", aTest, 0 >= lResult ? "PASSED" : "FAILED");	\
		return lResult;														\
	}																		\
																			\
	int RunTests(const char ** aTests, int aCount)							\
	{																		\
		printf("Executing indicated tests...\n\n");							\
		unsigned int lResult = 0;											\
																			\
		while (0 < aCount)													\
		{																	\
			lResult += RunTest(strtoul(*aTests, NULL, 10));					\
																			\
			aCount--;														\
			aTests++;														\
		}																	\
																			\
		DisplayResults(lResult);											\
		return lResult;														\
	}
