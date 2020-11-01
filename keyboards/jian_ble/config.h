#ifndef CONFIG_H
#define CONFIG_H

#define ENABLE_STARTUP_ADV_NOLIST

#define BLE_NUS_MIN_INTERVAL 30
#define BLE_NUS_MAX_INTERVAL 40
#define BLE_HID_MAX_INTERVAL 60
#define BLE_HID_SLAVE_LATENCY 5

/* USB Device descriptor parameter */
#define VENDOR_ID       0xBC42
#define PRODUCT_ID      0x0042
#define DEVICE_VER      0x0100
#define MANUFACTURER    Joric
#define PRODUCT         Jian BLE
#define DESCRIPTION     The Answer to the Ultimate Question of Life, the Universe, and at least Keyboards

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

#define DIODE_DIRECTION COL2ROW

// different Jian configs
//#define DIPS_ENABLE
#define PHYSICAL_LEDS_ENABLE
#define NUM_LOCK_LED_PIN PIN9
#define CAPS_LOCK_LED_PIN PIN12
#define SCROLL_LOCK_LED_PIN PIN13

//#define NUM_LOCK_INVERT  //uncomment this if you using n-mosfet
//#define CAPS_LOCK_INVERT  //uncomment this if you using n-mosfet
//#define SCROLL_LOCK_INVERT  //uncomment this if you using n-mosfet

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

/* define if matrix has ghost */
//#define MATRIX_HAS_GHOST

/* Set 0 if debouncing isn't needed */
#define DEBOUNCING_DELAY 5


/* Mechanical locking support. Use KC_LCAP, KC_LNUM or KC_LSCR instead in keymap */
#define LOCKING_SUPPORT_ENABLE
/* Locking resynchronize hack */
#define LOCKING_RESYNC_ENABLE

/* key combination for command */
#define IS_COMMAND() ( \
    keyboard_report->mods == (MOD_BIT(KC_LSHIFT) | MOD_BIT(KC_RSHIFT)) \
)

//#ifdef BACKLIGHT_ENABLE
#define BACKLIGHT_PIN PIN8
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
