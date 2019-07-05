@echo off

cd %~dp0

bash -c "cd ../../ && export NRFSDK15_ROOT=/mnt/c/SDK/nRF5_SDK_15.0.0_a53641a && make crkbd_ble/master" || exit

cd ..\..\.build

set file=crkbd_ble_master_default.hex

%~dp0/uf2conv.py %file% -c -f 0xADA52840

copy /Y flash.uf2 %~dp0\precompiled\master

echo Waiting for the UF2 drive. Press Reset twice...

:loop
if not exist e:\ goto :loop

timeout 1

copy flash.uf2 e:\

