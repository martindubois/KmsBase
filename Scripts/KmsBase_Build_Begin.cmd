@echo off

rem Author    KMS - Martin Dubois, P.Eng.
rem Copyright (C) 2020 KMS. All rights reserved.
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   KmsBase
rem File      Scripts\KmsBase_Build_Begin.cmd

echo Executing  KmsBase_Build_Begin.cmd %1  ...

rem ===== Initialisation ====================================================

set EXPORT_CMD="Export.cmd"
set EXPORT_CMD_TXT="Export.cmd.txt"
set INNO_COMPIL32="C:\Program Files (x86)\Inno Setup 5\Compil32.exe"
set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe"
set PRODUCT=%1
set TEST_CMD="Test.cmd"
set VERSION_H="Common/Version.h"

set KMS_VERSION_EXE="Import\Binaries\Release_32\KmsVersion.exe"

if not exist %KMS_VERSION_EXE% set KMS_VERSION_EXE="Debug\KmsVersion.exe"

set OPTIONS="%PRODUCT%.sln" /target:rebuild
set PRODUCT_ISS="%PRODUCT%.iss"

rem ===== Verification ======================================================

if ""==%1 (
	echo FATAL ERROR  Invalid command line
	echo Usage  Scripts\KmsBase_Build_Begin.cmd {Product}
	pause
	exit /B 10
)

if not exist %INNO_COMPIL32% (
	echo FATAL ERROR  %INNO_COMPIL32%  does not exist
	echo Install Inno Setup 5.6.1
	pause
	exit /B 20
)

if not exist %MSBUILD% (
	echo FATAL ERROR  %MSBUILD%  does not exist
    echo Install Visual Studio 2017
	pause
	exit /B 30
)

rem ===== End ===============================================================

echo  OK
