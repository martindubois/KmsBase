@echo off

rem  Auteur		KMS -	Martin Dubois, ing.
rem  Produit	KmsBase
rem  Fichier	Test.cmd
rem  Usage		Test.cmd

echo  Executing Test.cmd ...

rem  ===== Verification =====================================================

set FOR_EACH_CONFIG="ForEachConfig.cmd"
if not exist %FOR_EACH_CONFIG% (
    echo  FATAL ERROR : %FOR_EACH_CONFIG% does not exist
	pause
	exit /B 1
)

set FOR_EACH_CONFIG_DLL="ForEachConfig_DLL.cmd"
if not exist %FOR_EACH_CONFIG_DLL% (
    echo  FATAL ERROR : %FOR_EACH_CONFIG_DLL% does not exist
	pause
	exit /B 2
)

rem  ===== Execution ========================================================

call %FOR_EACH_CONFIG_DLL% DepCheck.exe
if ERRORLEVEL 1 (
    echo  ERROR : %FOR_EACH_CONFIG_DLL% reported an error - DepCheck.exe
	pause
	exit /B 3
)

call %FOR_EACH_CONFIG_DLL% DepCheck_Net.exe
if ERRORLEVEL 1 (
    echo  ERROR : %FOR_EACH_CONFIG_DLL% reported an error - DepCheck_Net.exe
	pause
	exit /B 4
)

call %FOR_EACH_CONFIG% KmsLib_Test.exe
if ERRORLEVEL 1 (
    echo  ERROR : %FOR_EACH_CONFIG% reported an error
	pause
	exit /B 5
)

rem  ===== Fin ==============================================================

echo  OK
