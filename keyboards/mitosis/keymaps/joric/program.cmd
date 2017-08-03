@echo off

for %%f in (%~dp0.) do set layout=%%~nxf

set path=C:\WinAVR-20100110\bin;%path%
set port=COM4
set keyboard=mitosis
set file=../../../../%keyboard%_%layout%.hex

bash -c "cd ../../../../ && make %keyboard%-%layout%" || exit

echo Waiting for %port% (press reset)...

:while1
MODE %port% | grep "RTS"
IF errorlevel 1 goto while1

avrdude -p atmega32u4 -P %port%  -cavr109  -b57600 -U flash:w:"%file%":i

