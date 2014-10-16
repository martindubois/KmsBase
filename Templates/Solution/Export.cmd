@echo off

rem  Auteur		:	KMS -	Martin Dubois, ing.
rem  Client		:	TODO
rem  Projet		:	TODO
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

set DST="K:\Export\TODO\TODO\%1"
if exist %DST% (
    echo  ERREUR FATALE : Le repertoire %DST% existe deja!
    pause
    exit /B 2   
)

rem  ===== Execution ========================================================

mkdir "%DST%"

rem  TODO  mkdir "%DST%\"

rem  TODO  xcopy /IKQS "" "%DST%\"

if ERRORLEVEL 1 (
    echo ERREUR : xcopy a rapporte une erreur!
    pause
    exit /B 3
)

rem  ===== Fin ==============================================================

echo OK!
