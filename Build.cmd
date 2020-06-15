@echo off

rem Author    KMS - Martin Dubois, P.Eng.
rem Copyright (C) 2020 KMS. All rights reserved.
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   KmsBase
rem File      Build.cmd
rem Usage     .\Build.cmd

echo Executing  Build.cmd  ...

rem ===== Initialisation ====================================================

set EXPORT_CMD="Export.cmd"
set INNO_COMPIL32="C:\Program Files (x86)\Inno Setup 5\Compil32.exe"
set KMS_VERSION="Debug\KmsVersion.exe"
set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Professional\MSBuild\15.0\Bin\MSBuild.exe"
set PRODUCT=KmsBase
set VERSION_H="Common/Version.h"

set OPTIONS="%PRODUCT%.sln" /target:rebuild

rem ===== Verification ======================================================

if not exist %INNO_COMPIL32% (
	echo FATAL ERROR  %INNO_COMPIL32%  does not exist
	echo Install Inno 5.6.1
	pause
	exit /B 10
)

if not exist %MSBUILD% (
	echo FATAL ERROR  %MSBUILD%  does not exist
    echo Install Visual Studio 2017 Professional
	pause
	exit /B 20
)

rem ===== Execution =========================================================

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 30
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 40
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 50
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 60
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 70
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 80
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 90
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 100
)

call Test.cmd
if ERRORLEVEL 1 (
    echo ERROR  Test.cmd reported an error - %ERRORLEVEL%
	pause
	exit /B 110
)

%KMS_VERSION% Common\Version.h Export.cmd.txt %PRODUCT%.iss
if ERRORLEVEL 1 (
	echo ERROR  %KMS_VERSION% Common\Version.h Export.cmd.txt %PRODUCT%.iss  failed - %ERRORLEVEL%
	pause
	exit /B 120
)

%INNO_COMPIL32% /cc %PRODUCT%.iss
if ERRORLEVEL 1 (
	echo ERROR  %INNO_COMPIL32% /cc %PRODUCT%.iss  failed - %ERRORLEVEL%
	pause
	exit /B 130
)

%KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%
if ERRORLEVEL 1 (
    echo  ERROR  %KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 140
)

rem ===== End ===============================================================

echo  OK
