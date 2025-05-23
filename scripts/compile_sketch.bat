@echo off
REM === Set environment variables ===
set ARDUINO_CLI=C:\ProgramData\chocolatey\bin\arduino-cli.exe
set FQBN=arduino:avr:nano
set SKETCH_DIR=%~dp0..\sketches\hil_demo
set BUILD_DIR=%~dp0..\bin

REM === Create build directory if not exists ===
if not exist "%BUILD_DIR%" (
    mkdir "%BUILD_DIR%"
)

REM === Compile the Arduino sketch ===
"%ARDUINO_CLI%" compile ^
    --fqbn %FQBN% ^
    --build-path "%BUILD_DIR%" ^
    "%SKETCH_DIR%"

IF %ERRORLEVEL% NEQ 0 (
    echo Arduino compile failed!
    exit /b %ERRORLEVEL%
)

echo Sketch compiled successfully to %BUILD_DIR%
