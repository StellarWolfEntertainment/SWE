@echo off
setlocal enabledelayedexpansion

echo [INFO] Standard multi-arch/config build script.
echo [INFO] For advanced/custom setups, use CMake directly.

REM ========================= [Check for CMake] =========================
where cmake >nul 2>&1
if errorlevel 1 (
    echo [ERROR] CMake not found in PATH. Please install it or add it to PATH.
    exit /b 1
)

REM ========================= [Initialize Variables] =========================
set "BUILD_DIR=%~1"
if "%BUILD_DIR%"=="" (
    set "BUILD_DIR=build"
)

REM ========================= [Build All Configs and Architectures] =========================
for %%C in (Debug Release) do (
    for %%A in (Win32 x64) do (
        echo "[INFO] === Building %%C | %%A ==="
        call :BuildProject "%BUILD_DIR%" "%%C" "%%A"
        if errorlevel 1 (
            echo [ERROR] Build failed for %%C %%A.
            exit /b 1
        )
    )
)
exit /b 0

REM ========================= [BuildProject Function] =========================
:BuildProject
setlocal

set "ROOT_BUILD_DIR=%~1"
set "BUILD_TYPE=%~2"
set "ARCH=%~3"
set "EXCLUDED_DIR=dist"

REM === Create build directory ===
if not exist "%ROOT_BUILD_DIR%" (
    mkdir "%ROOT_BUILD_DIR%"
)

REM === Configure CMake ===
cmake -S . -B "%ROOT_BUILD_DIR%" -A "%ARCH%" -DCMAKE_BUILD_TYPE="%BUILD_TYPE%"
if errorlevel 1 (
    echo [ERROR] CMake configuration failed for %BUILD_TYPE% %ARCH%.
    endlocal & exit /b 1
)

REM === Build the project ===
cmake --build "%ROOT_BUILD_DIR%" --config "%BUILD_TYPE%"
if errorlevel 1 (
    echo [ERROR] Build failed for %BUILD_TYPE% %ARCH%.
    endlocal & exit /b 1
)

REM === Clean build directory (excluding dist) ===
echo [INFO] Cleaning build directory "%ROOT_BUILD_DIR%" (excluding "%EXCLUDED_DIR%")...
for /D %%d in ("%ROOT_BUILD_DIR%\*") do if /I not "%%~nxd"=="%EXCLUDED_DIR%" rd /s /q "%%d"
for %%f in ("%ROOT_BUILD_DIR%\*") do if not "%%~nxf"=="%EXCLUDED_DIR%" del /f /q "%%f"

echo [INFO] Build completed successfully for %BUILD_TYPE% %ARCH%.
endlocal
exit /b 0
REM ========================= [End of Script] =========================