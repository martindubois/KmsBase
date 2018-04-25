
// Auteur   KMS - Martin Dubois, ing.
// Produit  KmsBase
// Fichier  KmsLib_Test/File.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== Includes ===========================================================
#include <KmsLib/Exception.h>
#include <KmsLib/File.h>
#include <KmsTest.h>

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(File_Base)

    // ===== Copy ===========================================================

    try
    {
        KmsLib::File::Copy("DoesNotExist.txt", "DoNotCare.txt");
        KMS_TEST_ASSERT(false);
    }
    catch (KmsLib::Exception * eE)
    {
        KMS_TEST_ERROR_INFO;
        eE->Write(stdout);
        KMS_TEST_ASSERT(KmsLib::Exception::CODE_COPY_FILE_ERROR == eE->GetCode());
    }

    // ===== Delete =========================================================

    try
    {
        KmsLib::File::Delete("DoesNotExist.txt");
        KMS_TEST_ASSERT(false);
    }
    catch (KmsLib::Exception * eE)
    {
        KMS_TEST_ERROR_INFO;
        eE->Write(stdout);
        KMS_TEST_ASSERT(KmsLib::Exception::CODE_DELETE_FILE_ERROR == eE->GetCode());
    }

    // ===== IsEqual ========================================================
    KMS_TEST_ASSERT( KmsLib::File::IsEqual("DoesNotExist_A.txt"           , "DoesNotExist_B.txt"           ));
    KMS_TEST_ASSERT(!KmsLib::File::IsEqual("DoesNotExist.txt"             , "KmsLib_Test\\File.cpp"        ));
    KMS_TEST_ASSERT( KmsLib::File::IsEqual("KmsLib_Test\\File.cpp"        , "KmsLib_Test\\File.cpp"        ));
    KMS_TEST_ASSERT(!KmsLib::File::IsEqual("KmsLib_Test\\File.cpp"        , "KmsLib_Test\\Dump.cpp"        ));
    KMS_TEST_ASSERT( KmsLib::File::IsEqual("KmsLib_Test\\KmsLib_Test.cpp" , "KmsLib_Test\\KmsLib_Test.cpp" ));
    KMS_TEST_ASSERT(!KmsLib::File::IsEqual("KmsLib_Test\\Tests\\FileA.txt", "KmsLib_Test\\Tests\\FileB.txt"));

    // ===== Move ===========================================================

    try
    {
        KmsLib::File::Move("DoesNotExist.txt", "DoNotCare.txt");
        KMS_TEST_ASSERT(false);
    }
    catch (KmsLib::Exception * eE)
    {
        KMS_TEST_ERROR_INFO;
        eE->Write(stdout);
        KMS_TEST_ASSERT(KmsLib::Exception::CODE_MOVE_FILE_ERROR == eE->GetCode());
    }

KMS_TEST_END_2
