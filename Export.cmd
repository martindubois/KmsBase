@echo off

rem  Auteur		:	KMS -	Martin Dubois, ing.
rem  Projet		:	KmsBase
rem  Fichier	:	Export.cmd

echo  Execution de Export.cmd %1 ...

rem  ===== Verification de l'argument =======================================

if ""=="%1" (
    echo  ERREUR FATALE : Ligne de commande invalide!
    echo  Usage : Export.cmd {Ma.Mi.Bu_Type}
    pause
    exit /B 1
)

rem  ====== Verification de l'environnement =================================

set DST="K:\Export\KmsBase\%1"
if exist %DST% (
    echo  ERREUR FATALE : Le repertoire %DST% existe deja!
    pause
    exit /B 2   
)

rem  ===== Execution ========================================================

mkdir "%DST%"
mkdir "%DST%\Includes"
mkdir "%DST%\Libraries"
mkdir "%DST%\Libraries\Debug_32"
mkdir "%DST%\Libraries\Debug_64"
mkdir "%DST%\Libraries\Release_32"
mkdir "%DST%\Libraries\Release_64"

xcopy /IKQS Debug\*.lib			"%DST%\Libraries\Debug_32"
xcopy /IKQS Includes\*.h		"%DST%\Includes"
xcopy /IKQS Release\*.lib		"%DST%\Libraries\Release_32"
xcopy /IKQS Scripts\*.cmd       "%DST%"
xcopy /IKQS x64\Debug\*.lib		"%DST%\Libraries\Debug_64"
xcopy /IKQS x64\Release\*.lib	"%DST%\Libraries\Release_64"

if ERRORLEVEL 1 (
    echo ERREUR : xcopy a rapporte une erreur!
    pause
    exit /B 3
)

rem  ===== Fin ==============================================================

echo OK!
