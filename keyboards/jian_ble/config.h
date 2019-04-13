/*
Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert
Copyright 2017 Biacco42
Copyright 2018 Sekigon
Copyright 2019 Joric

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CONFIG_H
#define CONFIG_H

#define BLE_NUS_MIN_INTERVAL 30
#define BLE_NUS_MAX_INTERVAL 40

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBC42
#define PRODUCT_ID      0x0042
#define DEVICE_VER      0x0100
#define MANUFACTURER    Joric
#define PRODUCT         Jian BLE
#define DESCRIPTION     The Answer to the Ultimate Question of Life, the Universe, and at least Keyboards

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 7

// different Jian configs
#define DIPS_ENABLE
#define PHYSICAL_LEDS_ENABLE
#define NUM_LOCK_LED_PIN PIN8
#define CAPS_LOCK_LED_PIN PIN9
#define SCROLL_LOCK_LED_PIN PIN12
#define NUM_LOCK_INVERT  //uncomment this if you using n-mosfet
#define CAPS_LOCK_INVERT  //uncomment this if you using n-mosfet
#define SCROLL_LOCK_INVERT  //uncomment this if you using n-mosfet

#ifdef NUM_LOCK_INVERT
#define SET_NUM_LOCK_LED() writePinHigh(NUM_LOCK_LED_PIN)
#define RESET_NUM_LOCK_LED() writePinLow(NUM_LOCK_LED_PIN)
#else
#define SET_NUM_LOCK_LED() writePinLow(NUM_LOCK_LED_PIN)
#define RESET_NUM_LOCK_LED() writePinHigh(NUM_LOCK_LED_PIN)
#endif // NUM_LOCK_INVERT

#ifdef CAPS_LOCK_INVERT
#define SET_CAPS_LOCK_LED() writePinHigh(CAPS_LOCK_LED_PIN)
#define RESET_CAPS_LOCK_LED() writePinLow(CAPS_LOCK_LED_PIN)
#else
#define SET_CAPS_LOCK_LED() writePinLow(CAPS_LOCK_LED_PIN)
#define RESET_CAPS_LOCK_LED() writePinHigh(CAPS_LOCK_LED_PIN)
#endif // CAPS_LOCK_INVERT

#ifdef SCROLL_LOCK_INVERT
#define SET_SCROLL_LOCK_LED() writePinHigh(SCROLL_LOCK_LED_PIN)
#define RESET_SCROLL_LOCK_LED() writePinLow(SCROLL_LOCK_LED_PIN)
#else
#define SET_SCROLL_LOCK_LED() writePinLow(SCROLL_LOCK_LED_PIN)
#define RESET_SCROLL_LOCK_LED() writePinHigh(SCROLL_LOCK_LED_PIN)
#endif // SCROLL_LOCK_INVERT



#define DIODE_DIRECTION ROW2COL

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCE    1

/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

//#ifdef BACKLIGHT_ENABLE
#define BACKLIGHT_PIN PIN13
#define BACKLIGHT_LEVELS 5
//#define BACKLIGHT_BREATHING //not working with splits right now
#define BREATHING_PERIOD 6
//#endif

/* ws2812 RGB LED */
#define RGB_DI_PIN PIN7
#define RGBLIGHT_TIMER
#define RGBLED_NUM 7    // Number of LEDs
//#define RGBLIGHT_ANIMATIONS //not working with splits right now
#define RGBLIGHT_HUE_STEP 8
#define RGBLIGHT_SAT_STEP 8
#define RGBLIGHT_VAL_STEP 8
#define RGBLIGHT_LIMIT_VAL 100
#define ws2812_PORTREG  PORTD
#define ws2812_DDRREG   DDRD

/*
 * Feature disable options
 *  These options are also useful to firmware size reduction.
 */

/* disable debug print */
//#define NO_DEBUG

/* disable print */
//#define NO_PRINT

/* disable action features */
//#define NO_ACTION_LAYER
//#define NO_ACTION_TAPPING
//#define NO_ACTION_ONESHOT
//#define NO_ACTION_MACRO
//#define NO_ACTION_FUNCTION

#endif
