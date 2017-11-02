@ECHO off

CALL util\setup.bat %*
IF ERRORLEVEL 1 GOTO fail

REM - ensure output dir
IF NOT EXIST %PREND_OUT% (MKDIR %PREND_OUT%)

CALL build_peng.bat
IF ERRORLEVEL 1 GOTO fail

CALL build_ptest.bat
IF ERRORLEVEL 1 GOTO fail

CALL build_pexe.bat
IF ERRORLEVEL 1 GOTO fail

ECHO.
ECHO ----------------------
ECHO copying dependencies
ECHO ----------------------
ECHO.

XCOPY /Q /Y %PREND_SDL2_DLL% %PREND_OUT%
IF ERRORLEVEL 1 GOTO fail

XCOPY /Q /Y %PREND_GLEW_DLL% %PREND_OUT%
IF ERRORLEVEL 1 GOTO fail

ECHO done

ECHO.
ECHO build successful!
GOTO :EOF

:fail
ECHO.
ECHO build failed