
// Author / Auteur    KMS - Martin Dubois, ing.
// Product / Produit  KmsBase
// File / Fichier     KmsLib_Test/TextFile.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== Includes/KmsLib ====================================================
#include <KmsLib/Exception.h>
#include <KmsLib/File.h>
#include <KmsLib/TextFile.h>
#include <KmsTest.h>

// Constants
/////////////////////////////////////////////////////////////////////////////

#define TEST_FOLDER "KmsLib_Test\\Tests"

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(TextFile_Base)
{
    KmsLib::TextFile lTF;

    // ===== FindFirstDiff ==================================================
    KMS_TEST_COMPARE(4, lTF.FindFirstDiff(TEST_FOLDER "\\FileA.txt", TEST_FOLDER "\\FileB.txt"));
    KMS_TEST_COMPARE(5, lTF.FindFirstDiff(TEST_FOLDER "\\FileA.txt", TEST_FOLDER "\\FileC.txt"));
    KMS_TEST_COMPARE(4, lTF.FindFirstDiff(TEST_FOLDER "\\FileC.txt", TEST_FOLDER "\\FileA.txt"));

    // ===== Create =========================================================

    lTF.Create("Test1.txt");
    lTF.Create("Test2.txt");

    try
    {
        lTF.Create("\\\\.txt");
    }
    catch (KmsLib::Exception * eE)
    {
        KMS_TEST_ERROR_INFO;
        eE->Write(stdout);
        KMS_TEST_COMPARE(KmsLib::Exception::CODE_FILE_OPEN_ERROR, eE->GetCode());
    }

    // ===== Open ===========================================================
    lTF.Open(TEST_FOLDER "\\FileA.txt");
    lTF.Open(TEST_FOLDER "\\FileB.txt");
}
KMS_TEST_END_2
