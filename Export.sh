#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Export.sh
# Usage    ./Export.sh {Ma.Mi.Bu_Type}

# CODE REVIEW  2019-07-22  KMS - Martin Dubois, ing.

echo  Executing Export.sh $1 ...

# ===== Verification ========================================================

if [ "$1" = "" ] ; then
    echo  USER ERROR : Invalid command line
    echo  Usage  ./Export.sh {Ma.Mi.Bu_Type}
    exit 1 ;
fi

DST=~/Export/KmsBase/$1_Linux
if test -d $DST ; then
    echo  USER ERROR : $DST already exist
    exit 2 ;
fi

# ===== Execution ===========================================================

mkdir $DST
mkdir $DST/Binaries
mkdir $DST/Includes
mkdir $DST/Includes/KmsLib
mkdir $DST/Includes/KmsLib/Linux
mkdir $DST/Libraries
mkdir $DST/Tests

cp DoxyFile_en.txt				 $DST
cp DoxyFile_fr.txt	    		 $DST

cp Binaries/KmsCopy              $DST/Binaries
cp Binaries/KmsLib_Test          $DST/Tests
cp Includes/*.h                  $DST/Includes
cp Includes/KmsLib/*.h           $DST/Includes/KmsLib
cp Includes/KmsLib/Linux/*.h	 $DST/Includes/KmsLib/Linux
cp Libraries/KmsLib.a            $DST/Libraries
cp Scripts/Import.sh             $DST

# ===== Fin =================================================================

echo  OK!

