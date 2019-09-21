# Jorne Pro Mini

Trying to use Pro Mini for the slave half. Does not work yet (hangs after start).

See crkbd_328p for the simpler example that actually works and does not hang.
The secret is to disable VUSB driver (see vusb/main.c).

Unfortunately B5 cannot be used as input on Pro Mini.
B5 (pin13) is a built-in LED with load resistor.

If you disconnect the resistor the matrix works.
Crkbd_328p runs fine and prints mesages to the UART at 57600 baud.
Still no OLED, master/slave serial connection or RGB.

![](https://i.imgur.com/HM5wx9k.jpg)

## Pro Micro
* [Product page](https://www.sparkfun.com/products/12640)
* [Schematic](http://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/Pro_Micro_v13b.pdf)
* [Pinout](https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/ProMicro16MHzv1.pdf)

## Pro Mini
* [Product page](https://www.sparkfun.com/products/11113)
* [Schematic](https://cdn.sparkfun.com/datasheets/Dev/Arduino/Boards/Arduino-Pro-Mini-v14.pdf)
* [Pinout](https://cdn.sparkfun.com/assets/d/5/2/f/0/ProMini16MHzv2.pdf)

## Hardware changes

* The second reset on Pro Mini should be desoldered to not touch the ground (see GND/GND side on Pro Micro)
* The built-in indicator LED at pin 13 (B5) should be desoldered because B5 it is used in the matrix as input

## Pinout

Pinout is vastly different as well, atmega328p has different wiring (those pins are actually PDxx without the P prefix):

```cpp
#if defined(__AVR_ATmega328P__) // Pro Mini
#define MATRIX_ROW_PINS { D4, D5, D6, D7 }
#define MATRIX_COL_PINS { C3, C2, C1, C0, B5, B4 }
#else // default Crkbd Pro Micro layout
#define MATRIX_ROW_PINS { D4, C6, D7, E6 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3 }
#endif
```

![](https://i.imgur.com/DgnWuBE.jpg)

![](https://i.imgur.com/V14d3vf.jpg)

## Crkbd Schematic

![](https://i.imgur.com/3FvwNdU.jpg)

![](https://i.imgur.com/FBFUenv.jpg)


