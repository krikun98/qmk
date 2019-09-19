set path=C:\SDK\WinAVR-20100110\bin;%path%

cd %~dp0\..\..

set keymap=jorne


bash -c "make crkbd:%keymap%" || exit

::bash -c "make crkbd:%keymap% RGB_MATRIX_SPLIT_RIGHT=yes" || exit

::timeout 3

::avrdude -p atmega32u4 -P COM11 -c avr109  -e -U flash:w:crkbd_rev1_%keymap%.hex

::avrdude -V -PCOM6 -carduino -p m328p -b 57600 -U flash:w:crkbd_rev1_%keymap%.hex


avrdude -V -PCOM6 -c arduino -p m328p -b 57600 -U flash:w:crkbd_rev1_%keymap%.hex
