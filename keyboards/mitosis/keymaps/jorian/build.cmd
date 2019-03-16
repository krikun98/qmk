@echo off

bash -c "cd ../../../../ && make mitosis:jorian" || exit

set path=C:\SDK\WinAVR-20100110\bin;%path%
cd ../../../../
avrdude -p atmega32u4 -P COM11 -c avr109  -U flash:w:mitosis_jorian.hex
