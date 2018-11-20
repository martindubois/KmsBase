#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Export.sh
# Usage    ./Export.sh {Ma.Mi.Bu_Type}

echo  Executing Export.sh $1 ...

# ===== Verification ========================================================

if [ "$1" = "" ] ; then
    echo  USER ERROR : Invalid command line
    echo  Usage  ./Export.sh {Ma.Mi.Bu_Type}
    exit 1 ;
fi

DST=Export/$1_Linux
if test -d $DST ; then
    echo  USER ERROR : $DST already exist
    exit 2 ;
fi

# ===== Execution ===========================================================

mkdir $DST
mkdir $DST/Includes
mkdir $DST/Includes/KmsLib
mkdir $DST/Includes/KmsLib/Linux
mkdir $DST/Libraries
mkdir $DST/Templates
mkdir $DST/Templates/DLL
mkdir $DST/Templates/DLL/_DocUser
mkdir $DST/Templates/Test
mkdir $DST/Templates/Test/_DocUser
mkdir $DST/Templates/Tool
mkdir $DST/Templates/Tool/_DocUser

cp *.txt						 $DST
cp Includes/*.h                  $DST/Includes
cp Includes/KmsLib/*.h           $DST/Includes/KmsLib
cp Includes/KmsLib/Linux/*.h	 $DST/Includes/KmsLib/Linux
cp Libraries/KmsLib.a            $DST/Libraries
cp Scripts/Import.sh             $DST
cp Templates/DLL/*.cpp           $DST/Templates/DLL
cp Templates/DLL/*.h             $DST/Templates/DLL
cp Templates/DLL/_DocUser/*.txt  $DST/Templates/DLL/_DocUser
cp Templates/Test/*.cpp          $DST/Templates/Test
cp Templates/Test/_DocUser/*.txt $DST/Templates/Test/_DocUser
cp Templates/Tool/*.cpp          $DST/Templates/Tool
cp Templates/Tool/_DocUser/*.txt $DST/Templates/Tool/_DocUser

# ===== Fin =================================================================

echo  OK!

