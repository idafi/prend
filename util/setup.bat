@ECHO off

REM - don't waste time if already set up
IF DEFINED CPU (
	IF "%1" == "" (GOTO skip)
	IF "%CPU%" == "%1" (GOTO skip)
)

ECHO.
ECHO ----------------------
ECHO setting up build environment
ECHO ----------------------
ECHO.

REM - get target cpu
IF "%1" == "" (SET CPU=x64) ELSE (SET CPU=%1)
IF NOT %CPU% == x64 IF NOT %CPU% == x86 GOTO badcpu

ECHO targeting win %CPU%

REM - get user environment
CALL util\setup_env.bat
IF ERRORLEVEL 1 GOTO fail

REM - user environment check
IF NOT DEFINED PREND_HOME (GOTO envmissing)
IF NOT DEFINED PREND_LLVM (GOTO envmissing)

REM - set output dir
SET PREND_OUT=%PREND_HOME%\bin\%CPU%

REM - set platform args for compiler
if %CPU% == x86 ( 
	SET ARCH="i386"
) ELSE ( 
	SET ARCH="x86_64"
)

REM - set up lib dependencies
SET PREND_SDL2=%PREND_HOME%\lib\SDL2-2.0.5
SET PREND_GLEW=%PREND_HOME%\lib\glew-2.1.0
SET PREND_FBX="%PREND_HOME%\lib\FBX SDK"
SET PREND_GTEST=%PREND_HOME%\lib\googletest

SET PREND_SDL2_INC=%PREND_SDL2%\include
SET PREND_GLEW_INC=%PREND_GLEW%\include
SET PREND_FBX_INC=%PREND_FBX%\include
SET PREND_GTEST_INC=%PREND_GTEST%\include

SET PREND_SDL2_LIB=%PREND_SDL2%\lib\%CPU%
SET PREND_GLEW_LIB=%PREND_GLEW%\lib\Release\%CPU%
SET PREND_FBX_LIB=%PREND_FBX%\lib\%CPU%
SET PREND_GTEST_LIB=%PREND_GTEST%\lib\release\%CPU%

SET PREND_SDL2_DLL=%PREND_SDL2%\bin\%CPU%\SDL2.dll
SET PREND_GLEW_DLL=%PREND_GLEW%\bin\Release\%CPU%\glew32.dll

ECHO done
GOTO :EOF

:envmissing
ECHO One or more environment variables aren't set -- did you add the right paths to setup_env?
ECHO PREND_HOME is %PREND_HOME%
ECHO PREND_LLVM is %PREND_LLVM%
GOTO fail

:badcpu
ECHO invalid cpu target specified ('%1'); expected x64 or x86
GOTO fail

:fail
EXIT /b 1

:skip
ECHO.
ECHO already targeting win %CPU% - skipping environment setup
EXIT /b 0