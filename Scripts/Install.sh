#!/bin/sh

# Author / Auteur	:	KMS -	Martin Dubois, ing.
# Product / Produit	:	KmsBase
# File / Fichier	:	Install.sh
# Usage				:	./Install.sh
#  The script must be run from the directory where it is / Le fichier de
#  commandes doit �tre execute a partir du repertoire ou il se trouve.

echo  Execution de Install.sh ...

# ===== Verification ========================================================

DST=/Software/KmsBase_2.4

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

cp Includes/*.h                  $DST/Includes
cp Includes/KmsLib/*.h           $DST/Includes/KmsLib
cp Includes/KmsLib/Linux/*.h     $DST/Includes/KmsLib/Linux
cp Includes/KmsLib/OpenCL/*.h    $DST/Includes/KmsLib/OpenCL
cp Libraries/KmsLib.a            $DST/Libraries
cp Templates/DLL/*.cpp           $DST/Templates/DLL
cp Templates/DLL/*.h             $DST/Templates/DLL
cp Templates/DLL/_DocUser/*.txt  $DST/Templates/DLL/_DocUser
cp Templates/Test/*.cpp          $DST/Templates/Test
cp Templates/Test/_DocUser/*.txt $DST/Templates/Test/_DocUser
cp Templates/Tool/*.cpp          $DST/Templates/Tool
cp Templates/Tool/_DocUser/*.txt $DST/Templates/Tool/_DocUser

# ===== Fin =================================================================

echo  OK!
