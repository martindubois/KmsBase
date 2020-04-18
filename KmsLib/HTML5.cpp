
// Author   KMS - Martin Dubois, P.Eng.
// Product  KmsBase
// File     KmsLib/HTML.cpp

// TEST COVERAGE 2020-04-18 KMS - Martin Dubois, P.Eng.

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <assert.h>
#include <stdio.h>

// ===== Includes ===========================================================
#include <KmsLib/Exception.h>
#include <KmsLib/HTML5.h>

// Macros
/////////////////////////////////////////////////////////////////////////////

#define  TAG_BE(T)                                            \
    void  T##_Begin (FILE * aFile) { Tag_Begin (aFile, #T); } \
    void  T##_End   (FILE * aFile) { Tag_End   (aFile, #T); }

#define  TAG_C(T)                                       \
    void  T## (FILE * aFile) { Tag_Begin (aFile, #T); }

#define  TAG_CBE(T)                                           \
    void  T(FILE * aFile, const char * aText)                 \
    {                                                         \
        T##_Begin (aFile);                                    \
        fprintf   (aFile, "%s", aText);                       \
        T##_End   (aFile);                                    \
    }                                                         \
    void  T##_Begin (FILE * aFile) { Tag_Begin (aFile, #T); } \
    void  T##_End   (FILE * aFile) { Tag_End   (aFile, #T); }

#define  TAG_CBE_S(T,F)                                         \
    void  T(FILE * aFile, const char * aS0, const char * aText) \
    {                                                           \
        T##_Begin (aFile, aS0);                                 \
        fprintf   (aFile, "%s", aText);                         \
        T##_End   (aFile);                                      \
    }                                                           \
    void  T##_Begin (FILE * aFile, const char * aS0)            \
    {                                                           \
        Tag_Begin_Begin (aFile, #T);                            \
        fprintf         (aFile, F, aS0);                        \
        Tag_Begin_End   (aFile);                                \
    }                                                           \
    void  T##_End(FILE * aFile) { Tag_End(aFile, #T); }

namespace KmsLib
{
    namespace HTML5
    {
        
        // Fonctions
        /////////////////////////////////////////////////////////////////////

        void  Close(FILE * aFile)
        {
            assert(NULL != aFile);

            int lRet = fclose(aFile);
            assert(0 == lRet);

            (void)(lRet);
        }

        void  Complete(FILE * aFile)
        {
            assert(NULL != aFile);

            body_End(aFile);
            html_End(aFile);

            Close(aFile);
        }

        FILE  * Create(const char * aFolder, const char * aFile, const char * aTitle)
        {
            assert(NULL != aFolder );
            assert(NULL != aFile   );
            assert(NULL != aTitle  );

            FILE * lResult = Open(aFolder, aFile);
            assert(NULL != lResult);

            DOCTYPE    (lResult);
            html_Begin (lResult);
            head_Begin (lResult);
                title  (lResult, aTitle);
            head_End   (lResult);
            body_Begin (lResult);

            return lResult;
        }

        FILE  * Open(const char * aFolder, const char * aFile)
        {
            assert(NULL != aFolder );
            assert(NULL != aFile   );

            char lFileName[2048];

            sprintf_s(lFileName, "%s\\%s.html", aFolder, aFile);

            FILE * lResult;

            int lRet = fopen_s(&lResult, lFileName, "w");
            if (0 != lRet)
            {
                char  lMsg[2048];

                sprintf_s(lMsg, "fopen_s( , \"%s\",  ) failed returning %d", lFileName, lRet);

                throw  new  Exception(Exception::CODE_FILE_OPEN_ERROR, "fopen_s( , ,  ) failed", lMsg, __FILE__, __FUNCTION__, __LINE__, lRet);
            }

            assert(NULL != lResult);

            return lResult;
        }

        TAG_CBE_S (a       , " href=\"%s\""  )
        TAG_CBE_S (abbr    , " title=\"%s\"" )
        TAG_CBE_S (acronym , " title=\"%s\"" )
        TAG_CBE   (address )
        TAG_CBE   (aside   )

        TAG_CBE   (b    )
        TAG_CBE   (big  )
        TAG_CBE_S (blockquote, " cite=\"%s\"")
        TAG_BE    (body )
        TAG_C     (br   )

        TAG_CBE(caption )
        TAG_CBE(center  )
        TAG_CBE(cite    )
        TAG_CBE(code    )

        TAG_CBE (dd      )
        TAG_CBE (del     )
        TAG_BE  (details )
        TAG_CBE (dfn     )
        TAG_BE  (div     )
        TAG_BE  (dl      )
        TAG_CBE (dt      )

        TAG_CBE(em)

        TAG_CBE(footer)

        void  h(FILE * aFile, unsigned int aH, const char * aText)
        {
            assert(NULL != aFile);
            assert(NULL != aText);

            h_Begin (aFile, aH);
            fprintf (aFile, "%s", aText);
            h_End   (aFile, aH);
        }

        void  h_Begin(FILE * aFile, unsigned int aH)
        {
            assert(NULL != aFile);

            fprintf(aFile, "<h%u>", aH);
        }

        void  h_End(FILE * aFile, unsigned int aH)
        {
            assert(NULL != aFile);

            fprintf(aFile, "</h%u>", aH);
        }

        TAG_BE  (head )
        TAG_C   (hr   )
        TAG_BE  (html )

        TAG_CBE (i   )
        TAG_CBE (ins )

        TAG_CBE(kbd )

        TAG_CBE(li)

        TAG_CBE(main)
        TAG_CBE(mark)

        TAG_BE(nav)

        TAG_BE(ol       )
        // TODO HTML5.optgroup TAG_BE(optgroup )

        TAG_CBE (p        )
        TAG_CBE (pre      )
        // TODO HTML5.progress TAG_C   (progress )

        TAG_CBE(q)

        TAG_CBE   (s       )
        TAG_CBE   (samp    )
        TAG_BE    (section )
        TAG_BE    (select  )
        TAG_CBE   (small   )
        TAG_CBE_S (span, " style=\"%s\"")
        TAG_CBE   (strike  )
        TAG_CBE   (strong  )
        TAG_CBE   (style   )
        TAG_CBE   (sub     )
        TAG_CBE   (summary )
        TAG_CBE   (sup     )

        TAG_BE  (table )
        TAG_BE  (tbody )
        TAG_CBE (td    )
        TAG_BE  (tfoot )
        TAG_CBE (th    )
        TAG_BE  (thead )
        TAG_CBE (title )
        TAG_BE  (tr    )

        TAG_CBE (u  )
        TAG_BE  (ul )

        TAG_CBE(var)

        void  DOCTYPE(FILE * aFile) { Tag(aFile, "!DOCTYPE", "html"); }

        void  Comment(FILE * aFile, const char * aText)
        {
            assert(NULL != aFile);
            assert(NULL != aText);

            Comment_Begin (aFile);
            fprintf       (aFile, "%s", aText);
            Comment_End   (aFile);
        }

        void  Comment_Begin(FILE * aFile)
        {
            assert(NULL != aFile);

            fprintf(aFile, "<!-- ");
        }

        void  Comment_End(FILE * aFile)
        {
            assert(NULL != aFile);

            fprintf(aFile, " -->");
        }

        // NOT TESTED HTML5
        void  Tag(FILE * aFile, const char * aTag)
        {
            Tag_Begin_Begin (aFile, aTag);
            Tag_End         (aFile);
        }

        void  Tag(FILE * aFile, const char * aTag, const char * aAttr)
        {
            assert(NULL != aFile );
            assert(NULL != aAttr );

            Tag_Begin_Begin (aFile, aTag);
            fprintf         (aFile, " %s", aAttr);
            Tag_End         (aFile);
        }

        void  Tag_Begin(FILE * aFile, const char * aTag)
        {
            Tag_Begin_Begin (aFile, aTag);
            Tag_Begin_End   (aFile);
        }

        // NOT TESTED HTML5
        void  Tag_Begin(FILE * aFile, const char * aTag, const char * aAttr)
        {
            assert(NULL != aFile );
            assert(NULL != aAttr );

            Tag_Begin_Begin (aFile, aTag);
            fprintf         (aFile, " %s", aAttr);
            Tag_Begin_End   (aFile);
        }

        void  Tag_Begin_Begin(FILE * aFile, const char * aTag)
        {
            assert(NULL != aFile );
            assert(NULL != aTag  );

            fprintf(aFile, "<%s", aTag);
        }

        void  Tag_Begin_End(FILE * aFile)
        {
            assert(NULL != aFile);

            fprintf(aFile, ">");
        }

        void  Tag_End(FILE * aFile)
        {
            assert(NULL != aFile);

            fprintf(aFile, " />");
        }

        void  Tag_End(FILE * aFile, const char * aTag)
        {
            assert(NULL != aFile );
            assert(NULL != aTag  );

            fprintf(aFile, "</%s>", aTag);
        }
    }
}