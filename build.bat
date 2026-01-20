@echo off
setlocal enabledelayedexpansion

:: 1. SPECIFY EXACT PATHS
set "VS_PATH=C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
set "VCPKG_TOOLCHAIN=C:\Users\Usera\vcpkg\scripts\buildsystems\vcpkg.cmake"
set "NINJA_EXE=C:\Users\Usera\ninja-win\ninja.exe"
set "QT_PATH=C:\Qt\6.10.1\msvc2022_64"
set "BUILD_DIR=build"

:: 2. LOAD MSVC ENVIRONMENT
if not exist "%VS_PATH%" (
    echo [ERROR] vcvars64.bat not found at: "%VS_PATH%"
    echo Please find the correct path to vcvars64.bat on your machine and update the script.
    pause
    exit /b 1
)

echo [INFO] Initializing MSVC Environment...
call "%VS_PATH%" > nul

:: 3. CLEAN & PREPARE BUILD DIR
if exist "%BUILD_DIR%" rmdir /s /q "%BUILD_DIR%"
mkdir "%BUILD_DIR%"

echo [INFO] Configuring with Ninja...
cmake -S . -B %BUILD_DIR% ^
  -G "Ninja" ^
  -DCMAKE_MAKE_PROGRAM="%NINJA_EXE%" ^
  -DCMAKE_TOOLCHAIN_FILE="%VCPKG_TOOLCHAIN%" ^
  -DVCPKG_TARGET_TRIPLET=x64-windows-static-md ^
  -DCMAKE_PREFIX_PATH="%QT_PATH%" ^
  -DCMAKE_BUILD_TYPE=Debug

if %ERRORLEVEL% NEQ 0 goto :error

echo [INFO] Building...
cmake --build %BUILD_DIR% --parallel

if %ERRORLEVEL% NEQ 0 goto :error

echo.
echo [SUCCESS] Build Complete.
pushd "%BUILD_DIR%"

if exist "FileEncrypterGUI.exe" (
    echo [INFO] Deploying Qt dependencies...
    %QT_PATH%\bin\windeployqt.exe --debug FileEncrypterGUI.exe

    echo [INFO] Launching Application...
    .\FileEncrypterGUI.exe
) else (
    echo [WARNING] Build finished but FileEncrypterGUI.exe was not found in %CD%
    goto :error
)

popd
endlocal
pause
exit /b 0

:error
echo.
echo [FAILURE] Build process failed. Look at the compiler output above.
if exist "%BUILD_DIR%" popd
pause
exit /b 1