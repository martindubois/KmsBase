@echo off

rem  Author / Auteur	:	KMS -	Martin Dubois, ing.
rem  Product / Produit	:	KmsBase
rem  File / Fichier		:	ForEachConfig.cmd

echo  Executing ForEachConfig.cmd %1 %2 %3 ...

rem  ===== Verification =====================================================

if "" == "%1" (
	echo  USER ERROR : Invalid command line!
	echo  Usage : call ForEachConfig.cmd {EXE} [Arg0] [Arg1]
	pause
	exit /B 1
)

set  BIN_32_DEBUG=Debug
if not exist "%BIN_32_DEBUG%" (
    echo  FATAL ERROR : %BIN_32_DEBUG% does not exist!
	pause
	exit /B 2
)

set  BIN_32_DEBUG_DLL=Debug_DLL
if not exist "%BIN_32_DEBUG_DLL%" (
    echo  FATAL ERROR : %BIN_32_DEBUG_DLL% does not exist!
	pause
	exit /B 3
)

set  BIN_32_RELEASE=Release
if not exist "%BIN_32_RELEASE%" (
    echo  FATAL ERROR : %BIN_32_RELEASE% does not exist!
	pause
	exit /B 4
)

set  BIN_32_RELEASE_DLL=Release_DLL
if not exist "%BIN_32_RELEASE_DLL%" (
    echo  FATAL ERROR : %BIN_32_RELEASE_DLL% does not exist!
	pause
	exit /B 5
)

set  BIN_64_DEBUG=x64\Debug
if not exist "%BIN_64_DEBUG%" (
    echo  FATAL ERROR : %BIN_64_DEBUG% does not exist!
	pause
	exit /B 6
)

set  BIN_64_DEBUG_DLL=x64\Debug_DLL
if not exist "%BIN_64_DEBUG%" (
    echo  FATAL ERROR : %BIN_64_DEBUG_DLL% does not exist!
	pause
	exit /B 7
)

set  BIN_64_RELEASE=x64\Release
if not exist "%BIN_64_RELEASE%" (
    echo  FATAL ERROR : %BIN_64_RELEASE% does not exist!
	pause
	exit /B 8
)

set  BIN_64_RELEASE_DLL=x64\Release_DLL
if not exist "%BIN_64_RELEASE_DLL%" (
    echo  FATAL ERROR : %BIN_64_RELEASE_DLL% does not exist!
	pause
	exit /B 9
)

rem  ===== Execution ========================================================

%BIN_32_DEBUG%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 32 bits - Debug - Failed!
	pause
	exit /B 10
)

%BIN_32_DEBUG_DLL%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 32 bits - Debug DLL - Failed!
	pause
	exit /B 11
)

%BIN_32_RELEASE%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 32 bits - Release - Failed!
	pause
	exit /B 12
)

%BIN_32_RELEASE_DLL%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 32 bits - Release DLL - Failed!
	pause
	exit /B 13
)

%BIN_64_DEBUG%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 64 bits - Debug - Failed!
	pause
	exit /B 14
)

%BIN_64_DEBUG_DLL%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 64 bits - Debug DLL - Failed!
	pause
	exit /B 15
)

%BIN_64_RELEASE%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 64 bits - Release - Failed!
	pause
	exit /B 16
)

%BIN_64_RELEASE_DLL%\%1 %2 %3
if ERRORLEVEL 1 (
    echo  ERROR : 64 bits - Release DLL - Failed!
	pause
	exit /B 17
)

rem  ===== Fin ==============================================================

echo OK!
