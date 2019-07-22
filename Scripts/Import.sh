#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Import.sh
# Usage    ./Import.sh {Destination}

# CODE REVIEW  2019-07-22  KMS - Martin Dubois, ing.

echo Executing  Import.sh $1  ...

# ===== Initialisation =======================================================

KMS_COPY=Binaries/KmsCopy

# ===== Verification =========================================================

if [ ! -d $1 ]
then
    echo ERROR  $1  does not exist
    exit 10
fi

# ===== Execution ============================================================

$KMS_COPY . $1 Import.sh.txt
if [ 0 != $? ] ; then
    echo ERROR  $KMS_COPY . $1 Import.sh.txt  failed
    exit 20
fi

# ===== End ==================================================================

echo OK
