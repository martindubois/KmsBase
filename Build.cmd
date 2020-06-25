@echo off

rem Author    KMS - Martin Dubois, P.Eng.
rem Copyright (C) 2020 KMS. All rights reserved.
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   KmsBase
rem File      Build.cmd
rem Usage     .\Build.cmd

rem CODE REVIEW 2020-06-24 KMS - Martin Dubois, P.Eng.

echo Executing  Build.cmd  ...

rem ===== Initialisation ====================================================

set SCRIPT_FOLDER=Scripts

set KMS_BASE_BUILD_BEGIN_CMD="%SCRIPT_FOLDER%\KmsBase_Build_Begin.cmd"
set KMS_BASE_BUILD_END_CMD="%SCRIPT_FOLDER%\KmsBase_Build_End.cmd"

rem ===== Execution =========================================================

call %KMS_BASE_BUILD_BEGIN_CMD% KmsBase
if ERRORLEVEL 1 (
	echo FATAL ERROR  call %KMS_BASE_BUILD_BEGIN_CMD% KmsBase  reported an error - %ERRORLEVEL%
	pause
	exit /B 10
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32  reported an error - %ERRORLEVEL%
	pause
	exit /B 20
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64  reported an error - %ERRORLEVEL%
	pause
	exit /B 30
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32  reported an error - %ERRORLEVEL%
	pause
	exit /B 40
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64  reported an error - %ERRORLEVEL%
	pause
	exit /B 50
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32  reported an error - %ERRORLEVEL%
	pause
	exit /B 60
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64  reported an error - %ERRORLEVEL%
	pause
	exit /B 70
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32  reported an error - %ERRORLEVEL%
	pause
	exit /B 80
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64  reported an error - %ERRORLEVEL%
	pause
	exit /B 90
)

call %KMS_BASE_BUILD_END_CMD%
if ERRORLEVEL 1 (
	echo FATAL ERROR  call %KMS_BASE_BUILD_END_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 100
)

rem ===== End ===============================================================

echo  OK
