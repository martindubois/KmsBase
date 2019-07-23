#!/bin/sh

# Author   KMS - Martin Dubois, ing.
# Product  KmsBase
# File     Clean.sh
# Usage    ./Clean.sh

# CODE REVIEW  2019-07-22  KMS - Martin Dubois, ing.

echo Executing  Clean.sh  ...

# ===== Execution ===========================================================

cd KmsLib
./Clean.sh
cd ..

cd KmsCopy
./Clean.sh
cd ..

cd KmsLib_Test
./Clean.sh
cd ..

# ===== End =================================================================

echo OK