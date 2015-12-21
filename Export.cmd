@echo off

rem  Auteur		KMS -	Martin Dubois, ing.
rem  Produit	KmsBase
rem  Fichier	Export.cmd
rem  Usage		Export.cmd {Ma.Mi.Bu_Type}

echo  Execution de Export.cmd %1 ...

rem  ===== Verification =====================================================

if ""=="%1" (
    echo  ERREUR FATALE : Ligne de commande invalide
    echo  Usage : Export.cmd {Ma.Mi.Bu_Type}
    pause
    exit /B 1
)

set DST="K:\Export\KmsBase\%1"
if exist %DST% (
    echo  ERREUR FATALE : Le repertoire %DST% existe deja
    pause
    exit /B 2   
)

set EXPORT_CMD_TXT="Export.cmd.txt"
if not exist %EXPORT_CMD_TXT% (
	echo  ERREUR FATALE : %EXPORT_CMD_TXT% n'existe pas
	pause
	exit /B 4
)

rem  La version Debug de KmsCopy est utilisee pour l'exportation de maniere a
rem  teste celle-ci.

set KMS_COPY="Debug\KmsCopy.exe"
if not exist %KMS_COPY% (
    echo  ERREUR FATALE : %KMS_COPY% n'existe pas
	pause
	exit /B 3
)

rem  ===== Execution ========================================================

%KMS_COPY% . %DST% %EXPORT_CMD_TXT%
if ERRORLEVEL 1 (
    echo  ERREUR : %KMS_COPY% reported an error
	pause
	exit /B 4
)

rem  ===== Fin ==============================================================

echo OK
