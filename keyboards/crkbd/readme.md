# Jorne Pro Mini

Trying to use Pro Mini for the slave half. Does not work yet (hangs after start).

See crkbd_328p for the simpler example that actually works and does not hang.
The secret is to disable VUSB driver (see vusb/main.c).
Unfortunately B5 cannot be used as input on Pro Mini.
B5 (pin13) is a built-in LED with load resistor.

This project is postponed for now.

## Pro Micro
* [Product page](https://www.sparkfun.com/products/12640)
* [Schematic](http://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/Pro_Micro_v13b.pdf)
* [Pinout](https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/ProMicro16MHzv1.pdf)

## Pro Mini
* [Product page](https://www.sparkfun.com/products/11113)
* [Schematic](https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/Arduino-Pro-Mini-v14.pdf)
* [Pinout](https://cdn.sparkfun.com/assets/d/5/2/f/0/ProMini16MHzv2.pdf)

Mind that the second reset on pro mini should be desoldered to not touch the ground.

Pinout is vastly different as well, atmega328p has different wiring, something like:

```
328p  32u4  328p
D1  D3   RAW  RAW
D0  D2   GND  GND
RST GND  RST  RST
GND GND  VCC  VCC
D2  D1    F4  C3
D3  D0    F5  C2
D4  D4    F6  C1
D5  C6    F7  C0
D6  D7    B1  B5
D7  E6    B3  B4
B0  B4    B2  B3
B1  B5    B6  B2 // Note E6, F4, F5, F6, F7 are not defined for 328p (lots of undefined symbol errors)
```

![](https://i.imgur.com/DgnWuBE.jpg)

![](https://i.imgur.com/POoLoaV.jpg)

## Crkbd Schematic

![](https://i.imgur.com/3FvwNdU.jpg)

![](https://i.imgur.com/FBFUenv.jpg)


