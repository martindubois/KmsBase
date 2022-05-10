@echo off

rem Author    KMS - Martin Dubois, P. Eng.
rem Copyright (C) 2022 KMS
rem License   http://www.apache.org/licenses/LICENSE-2.0
rem Product   KmsBase
rem File	  Export.cmd

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
mkdir "%DST%\Libraries\Debug_32_DLL"
mkdir "%DST%\Libraries\Debug_64"
mkdir "%DST%\Libraries\Debug_64_DLL"
mkdir "%DST%\Libraries\Release_32"
mkdir "%DST%\Libraries\Release_32_DLL"
mkdir "%DST%\Libraries\Release_64"
mkdir "%DST%\Libraries\Release_64_DLL"

xcopy /IKQS Debug\KmsLib.lib						"%DST%\Libraries\Debug_32"
xcopy /IKQS Debug_DLL\KmsLib.lib					"%DST%\Libraries\Debug_32_DLL"
xcopy /IKQS Includes\*.h							"%DST%\Includes"
xcopy /IKQS Release\KmsLib.lib						"%DST%\Libraries\Release_32"
xcopy /IKQS Release_DLL\KmsLib.lib					"%DST%\Libraries\Release_32_DLL"
xcopy /IKQS Scripts\*.cmd							"%DST%"
xcopy /IKQS x64\Debug\KmsLib.lib					"%DST%\Libraries\Debug_64"
xcopy /IKQS x64\Debug_DLL\KmsLib.lib				"%DST%\Libraries\Debug_64_DLL"
xcopy /IKQS x64\Release\KmsLib.lib					"%DST%\Libraries\Release_64"
xcopy /IKQS x64\Release_DLL\KmsLib.lib				"%DST%\Libraries\Release_64_DLL"

if ERRORLEVEL 1 (
    echo ERREUR : xcopy a rapporte une erreur!
    pause
    exit /B 3
)

rem  ===== Fin ==============================================================

echo OK!
