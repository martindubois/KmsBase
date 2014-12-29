@echo off

rem  Auteur		:	KMS -	Martin Dubois, ing.
rem	 Projet		:	KmsBase
rem  Fichier	:   Scripts/Install.cmd

echo  Execution de Install.cmd ...

rem  ===== Verification =====================================================

set DST="C:\Logiciels\KmsBase_2.1"

rem  ===== Execution ========================================================

xcopy /IKQSY Includes	%DST%\Includes
xcopy /IKQSY Libraries	%DST%\Libraries
xcopy /IKQSY Templates	%DST%\Templates

if ERRORLEVEL 1 (
    echo  ERREUR : xcopy a indique une erreur!
	pause
	exit /B 1
)

rem  ===== Fin ==============================================================

echo  OK!