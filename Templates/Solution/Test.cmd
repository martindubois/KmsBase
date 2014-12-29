@echo off

rem  Auteur		:	KMS -	Martin Dubois, ing.
rem  Client		:	TODO
rem  Projet		:	TODO
rem  Fichier	:	Test.cmd

echo  Execution de Test.cmd ...

rem  ===== Verification =====================================================

set  TODO_TEST=TODO_Test.exe

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

rem  ===== Execution ========================================================

%BIN_32_DEBUG%\%TODO_TEST%
if ERRORLEVEL 1 (
    echo  ERREUR FATALE : Le test 32 bit Debug a echoue!
	pause
	exit /B 1
)

%BIN_32_RELEASE%\%TODO_TEST%
if ERRORLEVEL 1 (
    echo  ERREUR FATALE : Le test 32 bit Release a echoue!
	pause
	exit /B 1
)

rem  ===== Fin ==============================================================

echo OK!
