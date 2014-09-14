@echo off

rem  Auteur		:	KMS -	Martin Dubois, ing.
rem  Projet		:	KmsBase
rem  Fichier	:	Test.cmd

echo  Execution de Test.cmd ...

rem  ===== Verification =====================================================

set  KMS_LIB_TEST=KmsLib_Test.exe

set  BIN_32_DEBUG=Debug
if not exist "%BIN_32_DEBUG%" (
    echo  ERREUR FATALE : Le repertoire %BIN_32_DEBUG% n'existe pas!
	pause
	exit /B 1
)

set  BIN_32_RELEASE=Release
if not exist "%BIN_32_RELEASE%" (
    echo  ERREUR FATALE : Le repertoire %BIN_32_RELEASE% n'existe pas!
	pause
	exit /B 1
)

set  BIN_64_DEBUG=Debug
if not exist "%BIN_64_DEBUG%" (
    echo  ERREUR FATALE : Le repertoire %BIN_64_DEBUG% n'existe pas!
	pause
	exit /B 1
)

set  BIN_64_RELEASE=Release
if not exist "%BIN_64_RELEASE%" (
    echo  ERREUR FATALE : Le repertoire %BIN_64_RELEASE% n'existe pas!
	pause
	exit /B 1
)

rem  ===== Execution ========================================================

%BIN_32_DEBUG%\%KMS_LIB_TEST%
if ERRORLEVEL 1 (
    echo  ERREUR FATALE : Le test 32 bit Debug a echoue!
	pause
	exit /B 1
)

%BIN_32_RELEASE%\%KMS_LIB_TEST%
if ERRORLEVEL 1 (
    echo  ERREUR FATALE : Le test 32 bit Release a echoue!
	pause
	exit /B 1
)

%BIN_64_DEBUG%\%KMS_LIB_TEST%
if ERRORLEVEL 1 (
    echo  ERREUR FATALE : Le test 64 bit Debug a echoue!
	pause
	exit /B 1
)

%BIN_64_RELEASE%\%KMS_LIB_TEST%
if ERRORLEVEL 1 (
    echo  ERREUR FATALE : Le test 64 bit Release a echoue!
	pause
	exit /B 1
)

rem  ===== Fin ==============================================================

echo OK!
