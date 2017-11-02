@ECHO off

IF NOT DEFINED CPU (GOTO envmissing)

ECHO.
ECHO ----------------------
ECHO building prend
ECHO ----------------------
ECHO.

clang++ ^
-target %ARCH%-windows-unknown ^
-c ^
-Xclang -flto-visibility-public-std ^
-g -gcodeview ^
-O0 ^
-std=c++17 ^
-Wall ^
-I%PREND_SDL2_INC% ^
-I%PREND_GLEW_INC% ^
-I%PREND_FBX_INC% ^
"src\prend\Shared\*.cpp" "src\prend\Shared\Logger\*.cpp" "src\prend\Core\*.cpp" "src\prend\Video\*.cpp"

IF ERRORLEVEL 1 GOTO :EOF

FOR %%f IN (*.o) DO (
	ECHO archiving %%f
	llvm-ar rvc lib\prend.lib %%f
)

llvm-ar rvc %PREND_SDL2_LIB%\SDL2main.lib
llvm-ar rvc %PREND_SDL2_LIB%\SDL2.lib
llvm-ar rvc %PREND_GLEW_LIB%\glew32s.lib
llvm-ar rvc %PREND_GLEW_LIB%\glew32.lib
llvm-ar rvc %PREND_FBX_LIB%\libfbxsdk-mt.lib

DEL *.o

ECHO done
GOTO :EOF

:envmissing
ECHO.
ECHO build environment isn't set up - did you forget to call setup.bat?

EXIT /b 1