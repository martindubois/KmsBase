@echo off

rem  Author / Auteur	KMS	-	Martin Dubois, ing.
rem  Product / Produit	KmsBase
rem  File / Fichier		Scripts/Verify.cmd
rem  Usage / Usage		Verify.cmd
rem
rem  The script must be run from the directory where it is / Le fichier de
rem  commandes doit être execute a partir du repertoire ou il se trouve.

echo  Executing Verify.cmd ...

rem  ===== Verification =====================================================

set DEP_CHECK="DepCheck.exe"
if not exist %DEP_CHECK% (
	echo  FATAL ERROR : %DEP_CHECK% does not exist
	echo  The package is not complete
	pause
	exit /B 1
)

set DEP_CHECK_NET="DepCheck_Net.exe"
if not exist %DEP_CHECK_NET% (
	echo  FATAL ERROR : %DEP_CHECK_NET% does not exist
	echo  The package is not complete
	pause
	exit /B 2
)

rem  ===== Execution ========================================================

%DEP_CHECK%
if ERRORLEVEL 1 (
	echo  ERROR : %DEP_CHECK% reported an error
	echo  Install the Visual Studio 12.0 redistributable
	pause
	exit /B 3
)

%DEP_CHECK_NET%
if ERRORLEVEL 1 (
	echo  ERROR : %DEP_CHECK_NET% reported an error
	echo  Install the .Net 4.5 framework
	pause /B 4
)

rem  ===== End / Fin ========================================================

echo  OK
