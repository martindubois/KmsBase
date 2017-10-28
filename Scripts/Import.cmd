@echo off

rem  Author / Auteur     KMS - Martin Dubois, ing.
rem  Product / Produit   KmsBase
rem  File / Fichier      Scripts/Import.cmd

echo  Executing  Import.cmd %1  ...

rem  ===== Arguments ========================================================

set DST=%1

rem  ===== Constants ========================================================

set KMS_COPY_EXE="Binaries\Release_32\KmsCopy.exe"

set IMPORT_CMD_TXT=Import.cmd.txt

rem  ===== Verification =====================================================

if "" == "%1" (
    echo  USER ERROR  Invalid command line
    echo  Usage  Import.cmd  {Output_Folder}
    pause
    exit /B 1
)

if not exist %DST% (
    echo  USER ERROR  %DST% does not exist
    pause
    exit /B 2
)

if not exist %KMS_COPY_EXE% (
    echo  FATAL ERROR  %KMS_COPY_EXE% does not exist
    echo  The package is not complete
    pause
    exit /B 3
)

if not exist %IMPORT_CMD_TXT% (
    echo  FATAL ERROR  %IMPORT_CMD_TXT% does not exist
    echo  The package is not complete
    pause
    exit /B 4
)

rem  ===== Execution ========================================================

%KMS_COPY_EXE% . %DST% %IMPORT_CMD_TXT%
if ERRORLEVEL 1 (
    echo  ERROR  %KMS_COPY_EXE% . %DST% %IMPORT_CMD_TXT%  reported an error - %ERRORLEVEL%
    echo  The package is not complete
    pause
    exit /B 5
)

rem  ===== End ==============================================================

echo  OK
