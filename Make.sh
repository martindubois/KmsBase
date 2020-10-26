#!/bin/sh

# Author    KMS - Martin Dubois, P.Eng.
# Copyright (C) 2020 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   KmsBase
# File      Make.sh
# Usage     ./Make.sh

# CODE REVIEW 2020-10-26 KMS - Martin Dubois, P.Eng.

echo Executing  Make.sh  ....

# ===== Execution ===========================================================

echo Building KmsLib
cd KmsLib
make
if [ 0 != $? ] ; then
    echo ERROR  KmsLib - make  failed
    exit 10
fi
cd ..

echo Building KmsCopy
cd KmsCopy
make
if [ 0 != $? ] ; then
    echo ERROR  KmsCopy - make  failed
    exit 15
fi
cd ..

echo Building KmsVersion
cd KmsVersion
make
if [ 0 != $? ] ; then
    echo ERROR  KmsVersion - make  failed
    exit 18
fi
cd ..

echo Building KmsLib_Test ...
cd KmsLib_Test
make
if [ 0 != $? ] ; then
    echo ERROR  KmsLib_Test - make  failed
    exit 20
fi
cd ..

# ===== End =================================================================

echo OK
