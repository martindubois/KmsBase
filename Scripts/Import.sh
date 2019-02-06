#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Import.sh
# Usage    ./Import.sh {Destination}

echo Executing  Import.sh $1  ...

# ===== Verification =========================================================

if [ ! -d $1 ]
then
    echo ERROR  $1  does not exist
    exit 1
fi

# ===== Execution ============================================================

mkdir $1/Includes
mkdir $1/Includes/KmsLib
mkdir $1/Includes/KmsLib/Linux
mkdir $1/Libraries

cp Includes/*.h              $1/Includes
cp Includes/KmsLib/*.h       $1/Includes/KmsLib
cp Includes/KmsLib/Linux/*.h $1/Includes/KmsLib/Linux
cp Libraries/*.a             $1/Libraries

# ===== End ==================================================================

echo OK
