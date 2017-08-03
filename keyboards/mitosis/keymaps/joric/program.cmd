setlocal EnableDelayedExpansion

@echo off

set path=C:\WinAVR-20100110\bin;%path%
set keyboard=mitosis
set ports=COM4 COM9

for %%f in (%~dp0.) do set layout=%%~nxf
set file=../../../../%keyboard%_%layout%.hex

bash -c "cd ../../../../ && make %keyboard%-%layout%" || exit

bash -c "ln -f %file% ../../../../precompiled"

echo Waiting for DFU (press reset)...

:loop
for %%x in (%ports%) do (
	set port=%%x
	MODE %%x | grep "RTS"
	IF "!errorlevel!"=="0" goto continue
)
goto loop

:continue
echo %port% detected.

avrdude -p atmega32u4 -P %port%  -cavr109  -b57600 -U flash:w:"%file%":i


