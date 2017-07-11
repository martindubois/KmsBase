@echo off

rem  Auteur    KMS - Martin Dubois, ing.
rem  Produit   KmsBase
rem  Fichier   Build.cmd
rem  Usage     Build.cmd

echo  Execution de Build.cmd ...

rem  ===== Verification =====================================================

set EXPORT_CMD="Export.cmd"
rem  Export.cmd est dans le depot git tout comme Build.cmd

set KMS_VERSION="C:\Software\KmsTools\KmsVersion.exe"
if not exist %KMS_VERSION% (
    echo  FATAL ERROR  %KMS_VERSION% does not exist
	echo  Install KmsTools version 2.3.3 or higher
	pause
	exit /B 1
)

set MSBUILD="C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe"
if not exist %MSBUILD% (
	echo  ERREUR FATAL : %MSBUILD% n'existe pas
	pause
	exit /B 2
)

set SOLUTION="KmsBase.sln"
if not exist %SOLUTION% (
	echo  ERREUR FATAL : %SOLUTION% n'existe pas
	pause
	exit /B 3
)

set TEMP_FILE="Temp.tmp"

rem  ===== Execution ========================================================

%KMS_VERSION% Common/Version.h Scripts/Install.cmd

set OPTIONS=%SOLUTIONS% /target:rebuild

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 4
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 5
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 6
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 7
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 8
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 9
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32  failed - %ERRORLEVEL%
	pause
	exit /B 10
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERROR  %MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64  failed - %ERRORLEVEL%
	pause
	exit /B 11
)

call Test.cmd
if ERRORLEVEL 1 (
    echo  ERROR  Test.cmd reported an error - %ERRORLEVEL%
	pause
	exit /B 12
)

%KMS_VERSION% -3q Common\Version.h > %TEMP_FILE%
set /p VERSION= < %TEMP_FILE%

%KMS_VERSION% -Iq Common\Version.h > %TEMP_FILE%
set /p INTERNAL= < %TEMP_FILE%

del %TEMP_FILE%

call %EXPORT_CMD% %VERSION% %INTERNAL%
if ERRORLEVEL 1 (
    echo  ERROR  %EXPORT_CMD%  reported an error - %ERRORLEVEL%
	pause
	exit /B 13
)

rem  ===== Fin ==============================================================

echo  OK
