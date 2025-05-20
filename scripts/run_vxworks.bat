@echo off
setlocal

if "%~1"=="" (
  echo ERROR: Must pass NETWORK_PATH as first argument
  exit /b 1
)

set NETPATH=%~1
set FQBN=arduino:avr:nano:cpu=atmega328old
set HEX=bin\hil_demo.hex
set TIMESTAMP=%date:~-4,4%%date:~-7,2%%date:~-10,2%_%time:~0,2%%time:~3,2%

echo Copying %HEX% to %NETPATH%...
copy /Y "%HEX%" "%NETPATH%\hil_demo_%TIMESTAMP%.hex"

echo Launching VxWorks client to load and run test script...
REM replace this with your real VxWorks launcher command
vxworks-loader-client --target 192.168.0.10 --load "%NETPATH%\hil_demo_%TIMESTAMP%.hex" --run-script test_sequence.ttl > "%NETPATH%\vxworks_log_%TIMESTAMP%.log"

echo VxWorks tests complete, log at %NETPATH%\vxworks_log_%TIMESTAMP%.log
