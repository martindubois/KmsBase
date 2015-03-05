@echo off

rem  Author / Auteur	:	KMS -	Martin Dubois, ing.
rem  Product / Produit	:	KmsBase
rem  File / Fichier		:	Test.cmd

echo  Executing Test.cmd ...

rem  ===== Verification =====================================================

set FOR_EACH_CONFIG="ForEachConfig.cmd"
if not exist %FOR_EACH_CONFIG% (
    echo  FATAL ERROR : %FOR_EACH_CONFIG% does not exist!
	pause
	exit /B 1
)

rem  ===== Execution ========================================================

call %FOR_EACH_CONFIG% KmsLib_Test.exe
if ERRORLEVEL 1 (
    echo  ERROR : %FOR_EACH_CONFIG% reported an error!
	pause
	exit /B 1
)

rem  ===== Fin ==============================================================

echo OK!
