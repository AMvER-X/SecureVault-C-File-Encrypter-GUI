@echo off
set VCPKG_TOOLCHAIN_PATH="C:\Users\Usera\vcpkg\scripts\buildsystems\vcpkg.cmake"
set BUILD_DIR=build

echo Starting C++ Project Build...

if not exist %BUILD_DIR% (
    mkdir %BUILD_DIR%
)

cd %BUILD_DIR% 

REM --- CMAKE Generation ---
REM use MinGW and the VCKPG Tooclhain

cmake .. -G "MinGW Makefiles" -DCMAKE_TOOLCHAIN_FILE=%VCPKG_TOOLCHAIN_PATH% -DVCPKG_TARGET_TRIPLET=x64-mingw-dynamic
if errorlevel 1 goto error

REM --- Compilation ---

mingw32-make 
if errorlevel 1 goto error

echo.
echo SUCCESS: Build Complete.

.\FileEncrypterGUI.exe

goto :eof

:error
echo.
echo FAILURE: Build process failed during CMake Generation or Compilation. Check error messages above.
pause