#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Export.sh

# CODE REVIEW  2019-07-22  KMS - Martin Dubois, ing.

echo  Executing Export.sh $1 ...

# ===== Initialisation ======================================================

DST=~/Export/KmsBase/$1_Linux

KMS_COPY=Binaries/KmsCopy

# ===== Verification ========================================================

if [ "$1" = "" ] ; then
    echo  USER ERROR  Invalid command line
    echo  Usage  ./Export.sh {Ma.Mi.Bu_Type}
    exit 10
fi

if test -d $DST ; then
    echo  USER ERROR  $DST  already exist
    exit 20
fi

if [ ! -x $KMS_COPY ] ; then
    echo  FATAL ERROR  $KMS_COPY  does not exist
    echo  Compile the project
    exit 30
fi

# ===== Execution ===========================================================

$KMS_COPY . $DST Export.sh.txt
if [ 0 != $? ] ; then
    echo ERROR  $KMS_COPY . $DST Export.sh.txt  failed
    exit 40
fi

# ===== End =================================================================

echo  OK!

