@echo off

rem Auteur   KMS - Martin Dubois, ing.
rem Produit  KmsBase
rem Fichier  Export.cmd
rem Usage    .\Export.cmd {Ma.Mi.Bu} [Type]

rem CODE REVIEW  2019-07-26  KMS - Martin Dubois, ing.

echo  Executing  Export.cmd %1 %2  ...

rem ===== Initialisation ====================================================

set EXPORT_TXT="Export.txt"

set EXPORT_CMD_TXT="Export.cmd.txt"

if ""=="%2" (
    set DST="K:\Export\KmsBase\%1_Windows"
) else (
    set DST="K:\Export\KmsBase\%1_%2_Windows"
)

rem La version Debug de KmsCopy est utilisee pour l'exportation de maniere a
rem tester celle-ci.

set KMS_COPY="Debug\KmsCopy.exe"

rem ===== Verification ======================================================

if ""=="%1" (
    echo  USER ERROR  Invalid command line
    echo  Usage : Export.cmd {Ma.Mi.Bu} [Internal|RC|Test]
    pause
    exit /B 10
)

if exist %DST% (
    echo  USER ERROR  %DST%  already exist
    pause
    exit /B 20
)

if not exist %KMS_COPY% (
    echo  FATAL ERROR  %KMS_COPY%  does not exist
    echo  Compile before exporting
    pause
    exit /B 30
)

rem ===== Execution =========================================================

%KMS_COPY% . %DST% %EXPORT_TXT%
if ERRORLEVEL 1 (
    echo  ERROR  %KMS_COPY% . %DST% %EXPORT_TXT%  failed - %ERRORLEVEL%
    pause
    exit /B 40
)

%KMS_COPY% . %DST% %EXPORT_CMD_TXT%
if ERRORLEVEL 1 (
    echo  ERROR  %KMS_COPY% . %DST% %EXPORT_CMD_TXT%  failed - %ERRORLEVEL%
    pause
    exit /B 50
)

rem ===== End ===============================================================

echo  OK
