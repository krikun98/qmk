# Jian BLE

Firmware for the Jian keyboard and the nRFMicro board

Please read this QMK nrf52 manual first (japanese only for now)

* https://github.com/sekigon-gonnoc/BLE-Micro-Pro

You have to flash Master and Slave firmwares separately, there's no unified firmware for both halves.

## Pairing

Pairing is a little bit weird. The init sequence is to erase all bonds first, then run advertising without whitelist.

**To reconnect master you need to run advertising without whitelist yet again, it doesn't connect automatically.**
So, every time you powering on the keyboard or the computer you need to press shortcut that runs advertising.
**Upd.** There's a define that helps, `#define ENABLE_STARTUP_ADV_NOLIST` but it probably doesn't help on powering on the computer.

Also there's a huge lag on the master keyboard.
Might be hardware problems (Bluetooth antenna on the flipped module is really blocked from all sides) might be software.
Most likely software, because slave, running wirelessly via USB-connected master has no lag at all.

If you're having problems with pairing to the slave keyboard, you need to erase bonds on the slave keyboard as well.
To reset bonds on the slave keyboard, press all 3 first keys on row 0 while powering on (it's modifier keys on Jian).
When halves are bonded there's no preferred order of powering them on, they will connect to each other anyway.

## Default layout

Adjust layer is activated by holding <kbd>Raise</kbd> and <kbd>Lower</kbd> simultaneously.
See original [Jian layout](http://www.keyboard-layout-editor.com/#/gists/4b6c2af67148f58ddd6c6b2976c4370f).

BLE and USB are enabled by default. You would like to restart advertising first.

* <kbd>Raise</kbd> + <kbd>Lower</kbd> + <kbd>AdvAll</kbd> restart advertising without whitelist.
* <kbd>Raise</kbd> + <kbd>Lower</kbd> + <kbd>UF2</kbd> open USB drive for firmware update

See [Jian BLE layout](http://www.keyboard-layout-editor.com/#/gists/3a6600e58e6d2e0e38c1bfa9e30988ec) for BLE shortcuts.
See [keymap.c](keymaps/default/keymap.c) for reference.
All shortcuts are subject to change in the future.

![](https://kle-render.herokuapp.com/api/3a6600e58e6d2e0e38c1bfa9e30988ec?2)

## Debugging

Every nrf52 keyboard creates two USB interfaces - USB HID and USB Serial for debugging.
Use terminal at 115200 baud to debug. You can debug Master and Slave simultaneously using two USB cables and two ports.

Example output:

```
<info> app: Erase all bonds!
<info> app: Fast advertising.
<info> app: Slave keyboard is disconnected
<info> app: Scanning slave keyboard...
<info> app: Connected to the slave keyboard
```



## Status

### Works

* Master and Slave via BLE (slave bonding is still funky, needs a few tries and resets).

### TODO

* CapsLock and other indicator LEDs
* Backlighting (flashes on init sequence for now, 3 times - master, 2 times - slave)
* Advanced keymap features and DIP switches
* RGB underglow

## nRFMicro pinout

* https://github.com/joric/nrfmicro/wiki/Hardware

## References

* https://github.com/sekigon-gonnoc/BLE-Micro-Pro (please read this)
* https://github.com/KGOH/qmk_firmware/tree/dev_branch/keyboards/jian
* https://github.com/joric/nrfmicro


