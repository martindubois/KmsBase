#!/bin/sh

# Auteur	:	KMS -	Martin Dubois, ing.
# Projet	:	KmsBase
# Fichier	:	Export.sh
# Usage		:	Export.sh {Ma.Mi.Bu_Type}

echo  Execution de Export.sh $1 ...

# ===== Verification ========================================================

if [ "$1" = "" ] ; then
    echo  ERREUR FATALE : Ligne de commande invalide!
	echo  Usage : ExportSources.sh {Ma.Mi.Bu_Type}
	exit 1
fi

DST=/k/Export/KmsBase/$1
if test ! -d $DST ; then
    echo  ERREUR FATALE : Le repertoire existe deja!
	exit 2
fi

# ===== Execution ===========================================================

mkdir $DST
mkdir $DST/Includes
mkdir $DST/Includes/KmsLib
mkdir $DST/Includes/KmsLib/OpenCL
mkdir $DST/Libraries
mkdir $DST/Libraries/Release_64
mkdir $DST/Templates
mkdir $DST/Templates/DLL
mkdir $DST/Templates/DLL/_DocUser
mkdir $DST/Templates/Driver_Linux
mkdir $DST/Templates/Test
mkdir $DST/Templates/Test/_DocUser
mkdir $DST/Templates/Tool

cp Includes/*.h                  $DST/Includes
cp Includes/KmsLib/*.h           $DST/Includes/KmsLib
cp Includes/KmsLib/OpenCL/*.h    $DST/Includes/KmsLib/OpenCL
cp Libraries/KmsLib.a            $DST/Libraries/Release_x64
cp Templates/DLL/*.cpp           $DST/Templates/DLL
cp Templates/DLL/*.h             $DST/Templates/DLL
cp Templates/DLL/_DocUser/*.txt  $DST/Templates/DLL/_DocUser
cp Templates/Driver_Linux/*.c    $DST/Templates/Driver_Linux
cp Templates/Driver_Linux/*.cpp  $DST/Templates/Driver_Linux
cp Templates/Driver_Linux/*.h    $DST/Templates/Driver_Linux
cp Templates/Test/*.cpp          $DST/Templates/Test
cp Templates/Test/_DocUser/*.txt $DST/Templates/Test/_DocUser
cp Templates/Tool/*.cpp          $DST/Templates/Tool
cp Templates/Tool/_DocUser/*.txt $DST/Templates/Tool/_DocUser

# ===== Fin =================================================================

echo  OK!

