@echo off

rem Auteur   KMS - Martin Dubois, ing.
rem Produit  KmsBase
rem Fichier  Import.cmd
rem Usage    .\Import.cmd {Destination}

rem CODE REVIEW  2019-07-26  KMS - Martin Dubois, ing.

echo Executing  Import.cmd %1  ...

rem ===== Initialisation ====================================================

set KMS_COPY_EXE="Binaries\Release_32\KmsCopy.exe"

rem ===== Verification ======================================================

if not exist %1 (
    echo USER ERROR  %1 does not exixt
    pause
    exit /B 10
)

if not exist %KMS_COPY_EXE% (
    echo FATAL ERROR  %KMS_COPY_EXE%  does not exist
    pause
    exit /B 20
)

rem ===== Execution =========================================================

%KMS_COPY_EXE% . %1 Import.txt
if ERRORLEVEL 1 (
    echo ERROR  %KMS_COPY_EXE% . %1 Import.txt  failed - %ERRORLEVEL
    pause
    exit /B 30
)

%KMS_COPY_EXE% . %1 Import.cmd.txt
if ERRORLEVEL 1 (
    echo ERROR  %KMS_COPY_EXE% . %1 Import.cmd.txt  failed - %ERRORLEVEL
    pause
    exit /B 40
)

rem ===== Fin ===============================================================

echo OK
