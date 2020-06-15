
// Author    KMS - Martin Dubois, P.Eng.
// Copyright (C) 2020 KMS. All rights reserved.
// License   http://www.apache.org/licenses/LICENSE-2.0
// Product   KmsBase
// File      KmsVersion/Version.h

#pragma once

// Classe
/////////////////////////////////////////////////////////////////////////////

class Version
{

public:

    Version();

    bool operator == (const Version & aB) const;
    bool operator != (const Version & aB) const;

    const char * GetText1(          ) const;
    const char * GetText2(          ) const;
    const char * GetText3(          ) const;
    const char * GetText4(char  aSep) const;

    void Parse(const char * aIn, char aSep);

    unsigned int mMajor ;
    unsigned int mMinor ;
    unsigned int mBuild ;
    unsigned int mCompat;

};
