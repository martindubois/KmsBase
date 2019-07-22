#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Import.sh
# Usage    ./Import.sh {Destination}

# CODE REVIEW  2019-07-22  KMS - Martin Dubois, ing.

echo Executing  Import.sh $1  ...

# ===== Verification =========================================================

if [ ! -d $1 ]
then
    echo ERROR  $1  does not exist
    exit 1
fi

# ===== Execution ============================================================

mkdir $1/Binaries
mkdir $1/Includes
mkdir $1/Includes/KmsLib
mkdir $1/Includes/KmsLib/Linux
mkdir $1/Libraries

cp Binaries/*                $1/Binaries
cp Includes/*.h              $1/Includes
cp Includes/KmsLib/*.h       $1/Includes/KmsLib
cp Includes/KmsLib/Linux/*.h $1/Includes/KmsLib/Linux
cp Libraries/*.a             $1/Libraries

# ===== End ==================================================================

echo OK
