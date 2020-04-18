
// Author / Auteur    KMS - Martin Dubois, ing.
// Product / Produit  KmsBase
// File / Fichier     KmsLib_Test/CmdLineParser.cpp

// Includes
/////////////////////////////////////////////////////////////////////////////

#include <KmsBase.h>

// ===== Interface ==========================================================
#include <KmsLib/Exception.h>
#include <KmsLib/HTML5.h>
#include <KmsTest.h>

#ifdef  small
    #undef  small
#endif  // small

// Tests
/////////////////////////////////////////////////////////////////////////////

KMS_TEST_BEGIN(HTML5_Base)
{
    try
    {
        KmsLib::HTML5::Open("DoesNotExist", "HTML5_Base");
        KMS_TEST_ERROR();
    }
    catch (KmsLib::Exception * eE)
    {
        KMS_TEST_ERROR_INFO;
        eE->Write(stdout);
        KMS_TEST_COMPARE(KmsLib::Exception::CODE_FILE_OPEN_ERROR, eE->GetCode());
    }

    FILE * lFile = KmsLib::HTML5::Open(".", "HTML5_Base");
    KMS_TEST_ASSERT(NULL != lFile);

    KmsLib::HTML5::Close(lFile);

    lFile = KmsLib::HTML5::Create(".", "HTML5_Base", "HTML5 Base");
    KMS_TEST_ASSERT_RETURN(NULL != lFile);

    KmsLib::HTML5::a      (lFile, "http://www.google.ca/", "Google");
    KmsLib::HTML5::abbr   (lFile, "Kernel Mode Software", "KMS");
    KmsLib::HTML5::acronym(lFile, "Kernel Mode Software", "KMS");
    KmsLib::HTML5::address(lFile, "mdubois@kms-quebec.com");
    KmsLib::HTML5::aside  (lFile, "aside");
    KmsLib::HTML5::b      (lFile, "Bold");
    KmsLib::HTML5::big    (lFile, "Big");
    KmsLib::HTML5::blockquote(lFile, "Martin Dubois", "Une verite qui n'est pas dite n'en demeure pas moins une verite.");
    KmsLib::HTML5::br     (lFile);
    KmsLib::HTML5::caption(lFile, "Caption");
    KmsLib::HTML5::center (lFile, "Center");
    KmsLib::HTML5::cite   (lFile, "Cite");
    KmsLib::HTML5::code   (lFile, "Code");
    KmsLib::HTML5::del    (lFile, "Deleted");
    KmsLib::HTML5::dfn    (lFile, "Definition");
    KmsLib::HTML5::em     (lFile, "Emphasized text");
    KmsLib::HTML5::footer (lFile, "Footer");
    KmsLib::HTML5::h      (lFile, 1, "H1");
    KmsLib::HTML5::hr     (lFile);
    KmsLib::HTML5::i      (lFile, "i");
    KmsLib::HTML5::ins    (lFile, "ins");
    KmsLib::HTML5::kbd    (lFile, "kbd");
    KmsLib::HTML5::main   (lFile, "main");
    KmsLib::HTML5::mark   (lFile, "mark");
    KmsLib::HTML5::p      (lFile, "p");
    KmsLib::HTML5::pre    (lFile, "pre");
    // TODO HTML5.progress KmsLib::HTML5::progress(lFile, 32, 100);
    KmsLib::HTML5::q      (lFile, "q");
    KmsLib::HTML5::s      (lFile, "s");
    KmsLib::HTML5::samp   (lFile, "samp");
    KmsLib::HTML5::small  (lFile, "small");
    KmsLib::HTML5::span   (lFile, "color:blue", "Blue");
    KmsLib::HTML5::strike (lFile, "strike");
    KmsLib::HTML5::strong (lFile, "strong");
    KmsLib::HTML5::style  (lFile, "h1 {color:red;}");
    KmsLib::HTML5::summary(lFile, "Summary");
    KmsLib::HTML5::sub    (lFile, "sub");
    KmsLib::HTML5::sup    (lFile, "sup");
    KmsLib::HTML5::u      (lFile, "u");
    KmsLib::HTML5::var    (lFile, "var");

    KmsLib::HTML5::details_Begin(lFile);
    KmsLib::HTML5::details_End  (lFile);

    KmsLib::HTML5::div_Begin(lFile);
    KmsLib::HTML5::div_End  (lFile);

    KmsLib::HTML5::dl_Begin(lFile);
        KmsLib::HTML5::dt(lFile, "Coffee");
        KmsLib::HTML5::dd(lFile, "Black hot drink");
    KmsLib::HTML5::dl_End  (lFile);

    KmsLib::HTML5::nav_Begin (lFile);
    KmsLib::HTML5::nav_End   (lFile);

    KmsLib::HTML5::ol_Begin (lFile);
        KmsLib::HTML5::li(lFile, "li");
    KmsLib::HTML5::ol_End   (lFile);

    // TODO HTML5.optgroup
    //      KmsLib::HTML5::optgroup_Begin(lFile, "Label");
    //      KmsLib::HTML5::optgroup_End  (lFile);

    KmsLib::HTML5::section_Begin(lFile);
    KmsLib::HTML5::section_End  (lFile);

    KmsLib::HTML5::select_Begin(lFile);
    KmsLib::HTML5::select_End  (lFile);

    KmsLib::HTML5::table_Begin (lFile);
        KmsLib::HTML5::thead_Begin (lFile);
            KmsLib::HTML5::tr_Begin (lFile);
                KmsLib::HTML5::th(lFile, "Header");
            KmsLib::HTML5::tr_End   (lFile);
        KmsLib::HTML5::thead_End   (lFile);
        KmsLib::HTML5::tbody_Begin (lFile);
            KmsLib::HTML5::tr_Begin(lFile);
                KmsLib::HTML5::td(lFile, "Data");
            KmsLib::HTML5::tr_End(lFile);
        KmsLib::HTML5::tbody_End   (lFile);
        KmsLib::HTML5::tfoot_Begin(lFile);
        KmsLib::HTML5::tfoot_End  (lFile);
    KmsLib::HTML5::table_End   (lFile);

    KmsLib::HTML5::ul_Begin (lFile);
        KmsLib::HTML5::li(lFile, "li");
    KmsLib::HTML5::ul_End   (lFile);

    KmsLib::HTML5::Comment(lFile, "Comment");

    KmsLib::HTML5::Complete(lFile);
}
KMS_TEST_END_2
