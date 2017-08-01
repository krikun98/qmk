@echo off
set conf=joric

bash -c "cd ../../../../ && make mitosis-%conf%"
IF errorlevel 1 exit

set file=..\..\..\..\mitosis_%conf%.hex

set port=COM9
echo Waiting for %port% (press reset)...
:loop1
MODE %port% | grep "RTS"
IF errorlevel 1 goto loop1

set path=C:\WinAVR-20100110\bin;%path%

avrdude -p atmega32u4 -P %port%  -cavr109  -b57600 -U flash:w:"%file%":i

