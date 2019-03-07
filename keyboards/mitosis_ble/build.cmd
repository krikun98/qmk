@echo off

set conf=slave

::set export=NRFSDK10_ROOT=/mnt/c/SDK/nRF51_SDK_10.0.0_dc26b5e
set export=NRFSDK12_ROOT=/mnt/c/SDK/nRF5_SDK_12.3.0_d7731ad

bash -c "cd ../../ && export %export% && make mitosis_ble/%conf%" || exit

set file=%~dp0\..\..\mitosis_ble_%conf%_default.hex
set eabi=C:\Users\User\AppData\Local\Arduino15\packages\adafruit\tools\gcc-arm-none-eabi\5_2-2015q4\bin
set path=%eabi%;%path%
set port=COM8

::set erase_opt=-ex "mon erase"

arm-none-eabi-gdb.exe --quiet --batch -ex "target extended-remote \\.\%port%" -ex "mon swdp_scan" ^
-ex "file %file:\=/%" -ex "att 1" %erase_opt% -ex load -ex run

