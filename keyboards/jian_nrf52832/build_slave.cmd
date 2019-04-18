@echo off

cd %~dp0

bash -c "cd ../../ && export NRFSDK12_ROOT=/mnt/c/SDK/nRF5_SDK_12.3.0_d7731ad && make jian_nrf52832/slave" || exit

cd ..\..\.build

set file=jian_nrf52832_slave_default.hex

set port=COM8

set path=C:\SDK\gcc-arm-none-eabi-8-2018-q4-major-win32\bin;%path%
arm-none-eabi-gdb.exe --quiet --batch -ex "target extended-remote \\.\%port%" -ex "mon swdp_scan" ^
-ex "file %file:\=/%" -ex "att 1" -ex load -ex run
