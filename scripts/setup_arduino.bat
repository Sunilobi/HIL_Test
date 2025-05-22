@echo off
setlocal

set ARDUINO_DATA=%ARDUINO_DATA%
set ARDUINO_USER_DIR=%ARDUINO_USER_DIR%

%ARDUINO_CLI% config init --overwrite --dest-dir %ARDUINO_DATA%
%ARDUINO_CLI% core update-index
%ARDUINO_CLI% core install arduino:avr

endlocal
