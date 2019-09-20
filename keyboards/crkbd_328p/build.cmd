set path=C:\SDK\WinAVR-20100110\bin;%path%

cd %~dp0\..\..

set keyboard=crkbd_328p
set keymap=default

bash -c "make %keyboard%:%keymap%" || exit

avrdude -V -PCOM6 -c arduino -p m328p -b 57600 -U flash:w:%keyboard%_%keymap%.hex
