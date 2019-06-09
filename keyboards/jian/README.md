# Jian

This is my fork of the original Jian firmware (I used n-mosfets for LEDs, see firmware settings).

## Downloads

* [jian_rev1_advanced.hex](precompiled/jian_rev1_advanced.hex) (precompiled firmware, both halves use the same firmware file)

### Uploading firmware

* press reset once (the desired Bootloader COM port appears in the device manager for a few seconds, so be fast).

* run this batch (COM12 is your ProMicro bootloader port, see yours in then device manager under COM ports):

`avrdude -p atmega32u4 -P COM12 -c avr109  -U flash:w:jian_rev1_advanced.hex`

## Keymap

[![](https://kle-render.herokuapp.com/api/390e5db8d649b006c32a5c49d4c82dab?0)](http://www.keyboard-layout-editor.com/#/gists/390e5db8d649b006c32a5c49d4c82dab)

* KLE: http://www.keyboard-layout-editor.com/#/gists/390e5db8d649b006c32a5c49d4c82dab

This keymap is an unmodified Jian keymap, I've just made a multi-layer version for the https://kle-render.herokuapp.com.
You can also check out the detailed multi-page versions:

* En: http://www.keyboard-layout-editor.com/#/gists/4b6c2af67148f58ddd6c6b2976c4370f

* Ru: http://www.keyboard-layout-editor.com/#/gists/9740d2bf0e1b98644100a7caa60be88a


## Enable backlight

* <kbd>Raise</kbd> + <kbd>Lower</kbd> + <kbd>Alt</kbd> toggle backlight mode (use <kbd>W</kbd> and <kbd>S</kbd> to adjust)


## Firmware settings

You may also use original firmware from here: https://github.com/KGOH/qmk_firmware/tree/dev_branch/keyboards/jian and fix the settings.
My build uses n-mosfets to save power, so I just uncommented these lines in [rev1/config.h](rev1/config.h):

```
#define NUM_LOCK_INVERT  //uncomment this if you using n-mosfet
#define CAPS_LOCK_INVERT  //uncomment this if you using n-mosfet
#define SCROLL_LOCK_INVERT  //uncomment this if you using n-mosfet
```

## Building Firmware

```
cd qmk_firmware
make git-submodule
make jian
```
Make git-submodule is only once.
The "make jian" command makes both advanced and default configurations (I use advanced for the backlight and probably some other options).


## Swapping the cable to the left or to the right

You can swap halves with <kbd>Raise</kbd> + <kbd>Lower</kbd> + <kbd>Shift</kbd> shortcut but to make it permanent you can use these patches:

### Cable plugged in to the left half (default, you don't need to do this)

`avrdude -p atmega32u4 -P COM12 -c avr109 -U eeprom:w:quantum/split_common/eeprom-lefthand.eep`

### Cable plugged in to the right half 

`avrdude -p atmega32u4 -P COM12 -c avr109 -U eeprom:w:quantum/split_common/eeprom-righthand.eep`

You need to patch BOTH halves with the SAME patch (patch both with lefthand or both with righthand).
 

## Pictures

![](https://i.imgur.com/sKOg8i2.jpg)

More pictures: https://imgur.com/a/QxZqppI

## Videos

[![](http://img.youtube.com/vi/RBCUeXvChKY/0.jpg)](https://youtu.be/RBCUeXvChKY)

## References

* https://github.com/KGOH/qmk_firmware/tree/dev_branch/keyboards/jian (original Jian repository)
* https://github.com/joric/nrfmicro/wiki/Jian-BLE (wireless nRFMicro version)
* https://redd.it/bfnd9k (original Jian GB thread)
