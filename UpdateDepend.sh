#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     UpdateDepend.sh
# Usage    ./UpdateDepend.sh

# CODE REVIEW  2019-07-22  KMS - Martin Dubois, ing.

echo Executing  UpdateDepend.sh  ....

# ===== Execution ===========================================================

echo Updating dependencies for KmsLib
cd KmsLib
make depend
if [ 0 != $? ] ; then
    echo ERROR  KmsLib - make depend  failed
    exit 10
fi
cd ..

echo Updating dependencies for KmsCopy
cd KmsCopy
make depend
if [ 0 != $? ] ; then
    echo ERROR  KmsCopy - make depend  failed
    exit 15
fi
cd ..

echo Updating dependencies for KmsLib_Test ...
cd KmsLib_Test
make depend
if [ 0 != $? ] ; then
    echo ERROR  KmsLib_Test - make depend  failed
    exit 20
fi
cd ..

# ===== End =================================================================

echo OK
