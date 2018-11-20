#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Build.sh
# Usage    ./Build.sh {Ma.Mi.Bu_Type}

echo  Executing  Build.sh $1  ...

# ===== Execution ============================================================

make clean

if [ $? -ne 0 ]
then
	echo  ERROR  make clean  failed - $?
	exit 1
fi

make

if [ $? -ne 0 ]
then
	echo  ERROR  make  failed - $?
	exit 2
fi

./Test.sh

if [ $? -ne 0 ]
then
	echo  ERROR  Test.sh  failed - $?
	exit 3
fi

./Export.sh $1

if [ $? -ne 0 ]
then
	echo  ERROR  Export.sh $1  failed - $?
	exit 4
fi

# ===== End ==================================================================

echo OK
