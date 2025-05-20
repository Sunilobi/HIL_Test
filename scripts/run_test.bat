@echo off
set PORT=COM3
set FQBN=arduino:avr:nano:cpu=atmega328old
set HEX_FILE=hil_demo.hex
set TIMESTAMP=%date:~-4,4%%date:~-7,2%%date:~-10,2%_%time:~0,2%%time:~3,2%

:: Flash the pre-compiled hex
arduino-cli upload -p %PORT% ^
    --fqbn %FQBN% ^
    --input-dir bin ^
    --verbose ^
    > logs\flash_%TIMESTAMP%.log

:: Run Teraterm test macro
"C:\Program Files (x86)\teraterm5\ttermpro.exe" ^
    /M="C:\HIL_Test\scripts\hil_test.ttl" ^
    /W="C:\HIL_Test\logs\serial_%TIMESTAMP%.log"

:: Verify test completion
findstr /C:"TEST_COMPLETE" logs\serial_%TIMESTAMP%.log || (
    echo ERROR: Test validation failed
    exit /b 1
)
echo SUCCESS: Hardware test passed
exit /b 0