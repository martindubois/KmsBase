@echo off

rem  Auteur	   KMS - Martin Dubois, ing.
rem  Produit   KmsBase
rem  Fichier   Export.cmd
rem  Usage     Export.cmd {Ma.Mi.Bu} [Internal|RC|Test]

echo  Execution de Export.cmd %1 %2 ...

rem  ===== Verification =====================================================

if ""=="%1" (
    echo  USER ERROR  Invalid command line
    echo  Usage : Export.cmd {Ma.Mi.Bu} [Internal|RC|Test]
    pause
    exit /B 1
)

if ""=="%2" (
	set DST="K:\Export\KmsBase\%1_Windows"
) else (
	set DST="K:\Export\KmsBase\%1_%2_Windows"
)

if exist %DST% (
    echo  USER ERROR  %DST%  already exist
    pause
    exit /B 2
)

set EXPORT_CMD_TXT="Export.cmd.txt"
rem   Export.cmd.txt est dans le depot GIT comme Build.cmd

rem  La version Debug de KmsCopy est utilisee pour l'exportation de maniere a
rem  tester celle-ci.

set KMS_COPY="Debug\KmsCopy.exe"
if not exist %KMS_COPY% (
    echo  FATAL ERROR  %KMS_COPY%  does not exist
	pause
	exit /B 3
)

rem  ===== Execution ========================================================

%KMS_COPY% . %DST% %EXPORT_CMD_TXT%
if ERRORLEVEL 1 (
    echo  ERROR  %KMS_COPY% . %DST% %EXPORT_CMD_TXT%  reported an error - %ERRORLEVEL%
	pause
	exit /B 4
)

rem  ===== Fin ==============================================================

echo  OK
