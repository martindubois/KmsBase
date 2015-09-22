#!/bin/sh

# Author / Auteur	:	KMS -	Martin Dubois, ing.
# Product / Produit	:	KmsBase
# File / Fichier	:	Export.sh
# Usage			:	Export.sh {Ma.Mi.Bu_Type}

echo  Executing Export.sh $1 ...

# ===== Verification ========================================================

if [ "$1" = "" ] ; then
    echo  USER ERROR : Invalid command line
    echo  Usage : ExportSources.sh {Ma.Mi.Bu_Type}
    exit 1 ;
fi

DST=Export/$1
if test -d $DST ; then
    echo  USER ERROR : $DST already exist
    exit 2 ;
fi

# ===== Execution ===========================================================

mkdir $DST
mkdir $DST/Includes
mkdir $DST/Includes/KmsLib
mkdir $DST/Includes/KmsLib/Linux
mkdir $DST/Includes/KmsLib/OpenCL
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
cp Includes/KmsLib/OpenCL/*.h    $DST/Includes/KmsLib/OpenCL
cp Libraries/KmsLib.a            $DST/Libraries
cp Scripts/Install.sh			 $DST
cp Templates/DLL/*.cpp           $DST/Templates/DLL
cp Templates/DLL/*.h             $DST/Templates/DLL
cp Templates/DLL/_DocUser/*.txt  $DST/Templates/DLL/_DocUser
cp Templates/Test/*.cpp          $DST/Templates/Test
cp Templates/Test/_DocUser/*.txt $DST/Templates/Test/_DocUser
cp Templates/Tool/*.cpp          $DST/Templates/Tool
cp Templates/Tool/_DocUser/*.txt $DST/Templates/Tool/_DocUser

# ===== Fin =================================================================

echo  OK!

