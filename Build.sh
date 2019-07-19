#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Build.sh
# Usage    ./Build.sh {Ma.Mi.Bu_Type}

# CODE REVIEW  2019-07-19  KMS - Martin Dubois, ing.

echo  Executing  Build.sh $1  ...

# ===== Execution ============================================================

./Clean.sh

./Make.sh
if [ $? -ne 0 ]
then
	echo  ERROR  ./Make.sh  failed - $?
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
