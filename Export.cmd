@echo off

rem  Auteur		KMS -	Martin Dubois, ing.
rem  Produit	KmsBase
rem  Fichier	Export.cmd
rem  Usage		Export.cmd {Ma.Mi.Bu} [Internal|RC|Test]

echo  Execution de Export.cmd %1 %2 ...

rem  ===== Verification =====================================================

if ""=="%1" (
    echo  ERREUR FATALE : Ligne de commande invalide
    echo  Usage : Export.cmd {Ma.Mi.Bu} [Internal|RC|Test]
    pause
    exit /B 1
)

if ""=="%2" (
	set DST="K:\Export\KmsBase\%1"
) else (
	set DST="K:\Export\KmsBase\%1_%2"
)

if exist %DST% (
    echo  ERREUR FATALE : Le repertoire %DST% existe deja
    pause
    exit /B 3
)

set EXPORT_CMD_TXT="Export.cmd.txt"
if not exist %EXPORT_CMD_TXT% (
	echo  ERREUR FATALE : %EXPORT_CMD_TXT% n'existe pas
	pause
	exit /B 4
)

rem  La version Debug de KmsCopy est utilisee pour l'exportation de maniere a
rem  tester celle-ci.

set KMS_COPY="Debug\KmsCopy.exe"
if not exist %KMS_COPY% (
    echo  ERREUR FATALE : %KMS_COPY% n'existe pas
	pause
	exit /B 5
)

set PACKAGES="K:\Packages"
if not exist %PACKAGES% (
	echo  ERREUR FATALE : %PACKAGES% n'existe pas
	pause
	exit /B 6
)

rem  ===== Execution ========================================================

%KMS_COPY% . %DST% %EXPORT_CMD_TXT%
if ERRORLEVEL 1 (
    echo  ERREUR : %KMS_COPY% reported an error
	pause
	exit /B 6
)

pushd kms.base.internal

	cpack --version=%1

popd

xcopy /K kms.base.internal\kms.base.internal.%1.nupkg %PACKAGES%
if ERRORLEVEL 1 (
	echo  ERREUR : xcopy a rapporte une erreur
	pause
	exit /B 8
)

if "Internal" == "%2" (
	echo  OK
	exit /B 0
)

pushd kms.base

	cpack --version=%1

popd

xcopy /K kms.base\kms.base.%1.nupkg %PACKAGES%
if ERRORLEVEL 1 (
	echo  ERREUR : xcopy a rapporte une erreur
	pause
	exit /B 7
)

rem  ===== Fin ==============================================================

echo  OK
