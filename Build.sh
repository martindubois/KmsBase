#!/bin/sh

# Author    KMS - Martin Dubois, P.Eng.
# Copyright (C) 2020 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   KmsBase
# File      Build.sh
# Usage     ./Build.sh {Ma.Mi.Bu_Type}

# CODE REVIEW 2020-08-26 KMS - Martin Dubois, P.Eng.

echo Executing  Build.sh $1  ...

# ===== Execution ============================================================

./Clean.sh

./Make.sh
if [ $? -ne 0 ]
then
	echo ERROR  ./Make.sh  failed
	exit 10
fi

./Test.sh

if [ $? -ne 0 ]
then
	echo ERROR  Test.sh  failed
	exit 20
fi

./CreatePackages.sh

if [ $? -ne 0 ]
then
	echo ERROR  CreatePackages.sh  failed
	exit 30
fi

./Export.sh $1

if [ $? -ne 0 ]
then
	echo ERROR  Export.sh $1  failed
	exit 40
fi

# ===== End ==================================================================

echo OK
