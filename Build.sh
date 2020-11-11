#!/bin/sh

# Author    KMS - Martin Dubois, P.Eng.
# Copyright (C) 2020 KMS
# License   http://www.apache.org/licenses/LICENSE-2.0
# Product   KmsBase
# File      Build.sh
# Usage     ./Build.sh

# CODE REVIEW 2020-11-11 KMS - Martin Dubois, P.Eng.

echo Executing  Build.sh  ...

# ===== Initialisation ======================================================

KMS_VERSION=Binaries/KmsVersion

VERSION_H=Common/Version.h

# ===== Verification ========================================================

if [ ! -x $KMS_VERSION ] ; then
    echo FATAL ERROR  $KMS_VERSION  does not exist
    echo Compile before exporting
    exit 5
fi

# ===== Execution ===========================================================

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

$KMS_VERSION $VERSION_H CreatePackages.sh Export.sh.txt

if [ $? -ne 0 ]
then
	echo ERROR  $KMS_VERSION $VERSION_H CreatePackages.sh Export.sh.txt  failed
	exit 25
fi

./CreatePackages.sh

if [ $? -ne 0 ]
then
	echo ERROR  ./CreatePackages.sh  failed
	exit 30
fi

$KMS_VERSION -S $VERSION_H ./Export.sh

if [ $? -ne 0 ]
then
	echo ERROR  $KMS_VERSION -S $VERSION_H ./Export.sh  failed
	exit 40
fi

# ===== End =================================================================

echo OK
