@echo off
setlocal

set ARDUINO_DATA=%ARDUINO_DATA%
set ARDUINO_USER_DIR=%ARDUINO_USER_DIR%

mkdir "%BUILD_DIR%" 2>nul || echo Build folder exists

%ARDUINO_CLI% compile ^
    --fqbn arduino:avr:nano:cpu=atmega328old ^
    --build-path "%BUILD_DIR%" ^
    sketches/hil_demo

endlocal
