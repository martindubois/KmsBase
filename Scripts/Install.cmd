@echo off

rem  Author / Auteur	KMS -	Martin Dubois, ing.
rem	 Product / Produit	KmsBase
rem  File / Fichier		Scripts/Install.cmd
rem  Usage				Install.cmd
rem
rem  The script must be run from the directory where it is / Le fichier de
rem  commandes doit être execute a partir du repertoire ou il se trouve.

echo  Executing de Install.cmd ...

rem  ===== Verification =====================================================

set DST="C:\Software\KmsBase_2.4"

set INSTALL_CMD_TXT="Install.cmd.txt"
if not exist %INSTALL_CMD_TXT% (
	echo  FATAL ERROR : %INSTALL_CMD_TXT% does not exist
	pause
	exit /B 1
)

set KMS_COPY="KmsCopy.exe"
if not exist %KMS_COPY% (
	echo  FATAL ERROR : %KMS_COPY% does not exist
	pause
	exit /B 2
)

rem  ===== Execution ========================================================

%KMS_COPY% . %DST% %INSTALL_CMD_TXT%

if ERRORLEVEL 1 (
	echo  FATAL ERROR : %KMS_COPY% reported an error
	pause
	exit /B 3
)

rem  ===== End / Fin ========================================================

echo  OK