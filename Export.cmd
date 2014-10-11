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
mkdir "%DST%\Libraries\Debug_32_DLL"
mkdir "%DST%\Libraries\Debug_64"
mkdir "%DST%\Libraries\Debug_64_DLL"
mkdir "%DST%\Libraries\Release_32"
mkdir "%DST%\Libraries\Release_32_DLL"
mkdir "%DST%\Libraries\Release_64"
mkdir "%DST%\Libraries\Release_64_DLL"
mkdir "%DST%\Templates"
mkdir "%DST%\Templates\DLL"
mkdir "%DST%\Templates\DLL\_DocUser"
mkdir "%DST%\Templates\Driver_KMDF"
mkdir "%DST%\Templates\Driver_KMDF\_DocUser"
mkdir "%DST%\Templates\Test"
mkdir "%DST%\Templates\Test\_DocUser"
mkdir "%DST%\Templates\Tool"
mkdir "%DST%\Templates\Tool\_DocUser"
mkdir "%DST%\Templates\Solution"
mkdir "%DST%\Templates\Solution\_DocUser"

xcopy /IKQS Debug\KmsLib.lib						"%DST%\Libraries\Debug_32"
xcopy /IKQS Debug_DLL\KmsLib.lib					"%DST%\Libraries\Debug_32_DLL"
xcopy /IKQS Includes\*.h							"%DST%\Includes"
xcopy /IKQS Release\KmsLib.lib						"%DST%\Libraries\Release_32"
xcopy /IKQS Release_DLL\KmsLib.lib					"%DST%\Libraries\Release_32_DLL"
xcopy /IKQS Scripts\*.cmd							"%DST%"
xcopy /IKQS Templates\DLL\*.cpp						"%DST%\Templates\DLL"
xcopy /IKQS Templates\DLL\*.h						"%DST%\Templates\DLL"
xcopy /IKQS Templates\DLL\_DocUser\*.txt			"%DST%\Templates\DLL\_DocUser"
xcopy /IKQS Templates\Driver_KMDF\*.cpp				"%DST%\Templates\Driver_KMDF"
xcopy /IKQS Templates\Driver_KMDF\*.h				"%DST%\Templates\Driver_KMDF"
xcopy /IKQS Templates\Driver_KMDF\*.inf				"%DST%\Templates\Driver_KMDF"
xcopy /IKQS Templates\Driver_KMDF\_DocUser\*.txt	"%DST%\Templates\Driver_KMDF\_DocUser"
rem  TODO : xcopy /IKQS Templates\Test\*.cpp			"%DST%\Templates\Test"
rem  TODO : xcopy /IKQS Templates\Test\_DocUser\*.txt	"%DST%\Templates\Test\_DocUser"
xcopy /IKQS Templates\Tool\*.cpp					"%DST%\Templates\Tool"
xcopy /IKQS Templates\Tool\*.h						"%DST%\Templates\Tool"
xcopy /IKQS Templates\Tool\_DocUser\*.txt			"%DST%\Templates\Tool\_DocUser"
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
