@echo off

rem  Auteur		KMS	-	Martin Dubois, ing.
rem  Produit	KmsBase
rem  Fichier	Build.cmd
rem  Usage		Build.cmd

echo  Execution de Build.cmd ...

rem  ===== Verification =====================================================

set MSBUILD="C:\Program Files (x86)\MSBuild\14.0\Bin\MSBuild.exe"
if not exist %MSBUILD% (
	echo  ERREUR FATAL : %MSBUILD% n'existe pas
	pause
	exit /B 1
)

set SOLUTION="KmsBase.sln"
if not exist %SOLUTION% (
	echo  ERREUR FATAL : %SOLUTION% n'existe pas
	pause
	exit /B 2
)

rem  ===== Execution ========================================================

set OPTIONS=%SOLUTIONS% /target:rebuild

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERREUR : Debug - Win32 - Failed
	pause
	exit /B 3
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERREUR : Debug - x64 - Failed
	pause
	exit /B 4
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERREUR : Debug_DLL - Win32 - Failed
	pause
	exit /B 5
)

%MSBUILD% %OPTIONS% /property:Configuration=Debug_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERREUR : Debug_DLL - x64 - Failed
	pause
	exit /B 6
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERREUR : Release - Win32 - Failed
	pause
	exit /B 7
)

%MSBUILD% %OPTIONS% /property:Configuration=Release /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERREUR : Release - x64 - Failed
	pause
	exit /B 8
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=Win32
if ERRORLEVEL 1 (
	echo  ERREUR : Release_DLL - Win32 - Failed
	pause
	exit /B 9
)

%MSBUILD% %OPTIONS% /property:Configuration=Release_DLL /property:Platform=x64
if ERRORLEVEL 1 (
	echo  ERREUR : Release_DLL - x64 - Failed
	pause
	exit /B 10
)

rem  ===== Fin ==============================================================

echo  OK
