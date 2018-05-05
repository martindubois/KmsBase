@echo off

rem Auteur   KMS - Martin Dubois, ing.
rem Produit  KmsBase
rem Fichier  Build.cmd
rem Usage    Build.cmd

echo  Executing  Build.cmd  ...

rem ===== Initialisation ====================================================

set EXPORT_CMD="Export.cmd"
set KMS_VERSION="C:\Software\KmsTools\KmsVersion.exe"
set MSBUILD="C:\Program Files (x86)\Microsoft Visual Studio\2017\Enterprise\MSBuild\15.0\Bin\MSBuild.exe"
set OPTIONS="KmsBase.sln" /target:rebuild
set VERSION_H="Common/Version.h"

rem ===== Verification ======================================================

if not exist %KMS_VERSION% (
    echo FATAL ERROR  %KMS_VERSION%  does not exist
	echo Install KmsTools version 2.4.0 or higher
	pause
	exit /B 1
)

if not exist %MSBUILD% (
	echo FATAL ERROR  %MSBUILD%  does not exist
    echo Install Visual Studio 2015
	pause
	exit /B 2
)

rem ===== Execution =========================================================

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 3
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 4
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 5
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 6
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 7
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 8
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 9
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 10
)

call Test.cmd
if ERRORLEVEL 1 (
    echo ERROR  Test.cmd reported an error - %ERRORLEVEL%
	pause
	exit /B 11
)

%KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%
if ERRORLEVEL 1 (
    echo  ERROR  %KMS_VERSION% -S %VERSION_H% %EXPORT_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 12
)

rem  ===== Fin ==============================================================

echo  OK
