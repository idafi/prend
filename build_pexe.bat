@ECHO off

IF NOT DEFINED CPU (GOTO envmissing)

ECHO.
ECHO ----------------------
ECHO building pexe
ECHO ----------------------
ECHO.

clang++ ^
-target %ARCH%-windows-unknown ^
-Xclang -flto-visibility-public-std ^
-g -gcodeview ^
-O0 ^
-std=c++17 ^
-Wall ^
-l"OpenGL32.lib" ^
-I%PREND_SDL2_INC% -L%PREND_SDL2_LIB% -lSDL2main.lib -lSDL2.lib ^
-I%PREND_GLEW_INC% -L%PREND_GLEW_LIB% -lglew32s.lib -lglew32.lib ^
-I%PREND_FBX_INC% -L%PREND_FBX_LIB% -llibfbxsdk-mt.lib ^
-llib\prend.lib ^
-Xlinker /subsystem:windows ^
-o"%PREND_OUT%/pexe.exe" ^
"src\pexe\pexe.cpp"

IF ERRORLEVEL 1 GOTO :EOF

ECHO done
GOTO :EOF

:envmissing
ECHO.
ECHO build environment isn't set up - did you forget to call setup.bat?
EXIT /b 1