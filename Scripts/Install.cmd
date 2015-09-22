@echo off

rem  Author / Auteur	:	KMS -	Martin Dubois, ing.
rem	 Product / Produit	:	KmsBase
rem  File / Fichier		:   Scripts/Install.cmd
rem  Usage				:	Install.cmd
rem  The script must be run from the directory where it is / Le fichier de
rem  commandes doit être execute a partir du repertoire ou il se trouve.

echo  Execution de Install.cmd ...

rem  ===== Verification =====================================================

set DST="C:\Software\KmsBase_2.4"

rem  ===== Execution ========================================================

xcopy /IKQSY DoxyFile_en.txt	%DST%
xcopy /IKQSY DoxyFile_fr.txt	%DST%
xcopy /IKQSY RunDoxygen.cmd		%DST%
xcopy /IKQSY Includes			%DST%\Includes
xcopy /IKQSY Libraries			%DST%\Libraries
xcopy /IKQSY Templates			%DST%\Templates

if ERRORLEVEL 1 (
    echo  ERROR : xcopy reported an error
	pause
	exit /B 1
)

rem  ===== Fin ==============================================================

echo  OK