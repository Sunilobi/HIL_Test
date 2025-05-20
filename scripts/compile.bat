@echo off
setlocal

:: Configure paths
set ARDUINO_DIR=C:\Arduino15
set ARDUINO_CLI_CONFIG=%ARDUINO_DIR%\arduino-cli.yaml
set SKETCH_NAME=hil_demo
set FQBN=arduino:avr:nano:cpu=atmega328old

:: Initialize config
if not exist "%ARDUINO_DIR%" mkdir "%ARDUINO_DIR%"
if not exist "%ARDUINO_CLI_CONFIG%" (
  arduino-cli config init --config-file "%ARDUINO_CLI_CONFIG%"
)

:: Install core
arduino-cli --config-file "%ARDUINO_CLI_CONFIG%" core update-index
arduino-cli --config-file "%ARDUINO_CLI_CONFIG%" core install arduino:avr

:: Compile
arduino-cli compile --config-file "%ARDUINO_CLI_CONFIG%" ^
  --fqbn %FQBN% ^
  --build-path bin ^
  sketches\%SKETCH_NAME%

:: Verify
if exist "bin\%SKETCH_NAME%.ino.hex" (
  echo SUCCESS | tee -a "%ARDUINO_DIR%\build.log"
  exit /b 0
) else (
  echo FAILED | tee -a "%ARDUINO_DIR%\build.log"
  exit /b 1
)