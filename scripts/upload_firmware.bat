@echo off
setlocal

set ARDUINO_DATA=%ARDUINO_DATA%
set ARDUINO_USER_DIR=%ARDUINO_USER_DIR%

%ARDUINO_CLI% upload ^
    --fqbn arduino:avr:nano:cpu=atmega328old ^
    --port %COM_PORT% ^
    --input-dir "%BUILD_DIR%" ^
    sketches/hil_demo

endlocal
