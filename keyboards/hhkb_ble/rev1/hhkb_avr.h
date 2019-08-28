#ifndef HHKB_AVR_H
#define HHKB_AVR_H

#include <stdint.h>
#include <stdbool.h>
#include <quantum.h>

#include "nrf_gpio.h"

#define setPinOutput nrf_gpio_cfg_output
#define setPinInputHigh(x) nrf_gpio_cfg_input(x, NRF_GPIO_PIN_PULLDOWN)
#define writePinHigh nrf_gpio_pin_set
#define writePinLow nrf_gpio_pin_clear
#define readPin nrf_gpio_pin_read

#define _delay_us nrf_delay_us

#include "pin_assign.h"

/*
 * HHKB Matrix I/O
 *
 * row:     HC4051[A,B,C]  selects scan row0-7
 * row-ext: [En0,En1] row extention for JP
 * col:     LS145[A,B,C,D] selects scan col0-7 and enable(D)
 * key:     on: 0/off: 1
 * prev:    hysteresis control: assert(1) when previous key state is on
 */

enum {
    HHKB_KEY_PIN = 0,    /* ~KEY: Low(0) when key is pressed (input with pullup) */
    HHKB_KEY_PREV_PIN,   /* HYS: High(1) when key is pressed (output) */
    HHKB_ROW_BIT0_PIN,   /* A(bit0) select row 0-7 (output) */
    HHKB_ROW_BIT1_PIN,   /* B(bit1) select row 0-7 (output) */
    HHKB_ROW_BIT2_PIN,   /* C(bit2) select row 0-7 (output) */
    HHKB_COL_BIT0_PIN,   /* A(bit0) select column 0-7 (output) */
    HHKB_COL_BIT1_PIN,   /* B(bit1) select column 0-7 (output) */
    HHKB_COL_BIT2_PIN,   /* C(bit2) select column 0-7 (output) */
    HHKB_COL_SELECT_PIN, /* ~D(enable) Low(0) enables selected column (output) */
#ifdef HHKB_POWER_SAVING
    HHKB_POWER_PIN,
#endif
#ifdef HHKB_JP
    HHKB_JP_COL_BIT3_PIN,   /* ~Enable of Z2   row0-7  (output) */
    HHKB_JP_COL_BIT4_PIN,   /* ~Enable of Z3   row8-15 (output) */
#endif
    HHKB_PINS_COUNT
} HHKB_pins_enum;

/*
    NOTE: Probably HYS changes threshold for upstroke and makes hysteresis in the result.
    NOTE: HYS should be given High(1) when previous KEY state is Low(0).
    NOTE: 1KOhm didn't work as pullup resistor on KEY. AVR internal pullup or 10KOhm resistor was OK.
    NOTE: JP has two HC4051(Z2,Z3) and line 5, 6 and 7 are connected to both of them.
*/

static const uint32_t HHKB_pins[HHKB_PINS_COUNT] = HHKB_PINS_HBAR;

static inline void KEY_ENABLE(void) { writePinLow(HHKB_pins[HHKB_COL_SELECT_PIN]); }
static inline void KEY_UNABLE(void) { writePinHigh(HHKB_pins[HHKB_COL_SELECT_PIN]); }
static inline bool KEY_STATE(void) { return readPin(HHKB_pins[HHKB_KEY_PIN]); }
static inline void KEY_PREV_ON(void) { writePinHigh(HHKB_pins[HHKB_KEY_PREV_PIN]); }
static inline void KEY_PREV_OFF(void) { writePinLow(HHKB_pins[HHKB_KEY_PREV_PIN]); }

#ifdef HHKB_POWER_SAVING
static inline void KEY_POWER_ON(void) {
    writePinHigh(HHKB_pins[HHKB_POWER_PIN]); // MOS FET switch on
    /* Without this wait you will miss or get false key events. */
    _delay_ms(5);                       // wait for powering up
}
static inline void KEY_POWER_OFF(void) {
    writePinLow(HHKB_pins[HHKB_POWER_PIN]);  // MOS FET switch off
}
static inline bool KEY_POWER_STATE(void) { return readPin(HHKB_pins[HHKB_POWER_PIN]); }
#else
static inline void KEY_POWER_ON(void) {}
static inline void KEY_POWER_OFF(void) {}
static inline bool KEY_POWER_STATE(void) { return true; }
#endif

static inline void KEY_INIT(void)
{
    setPinInputHigh(HHKB_pins[HHKB_KEY_PIN]);
    setPinOutput(HHKB_pins[HHKB_ROW_BIT0_PIN]);
    setPinOutput(HHKB_pins[HHKB_ROW_BIT1_PIN]);
    setPinOutput(HHKB_pins[HHKB_ROW_BIT2_PIN]);
    setPinOutput(HHKB_pins[HHKB_COL_BIT0_PIN]);
    setPinOutput(HHKB_pins[HHKB_COL_BIT1_PIN]);
    setPinOutput(HHKB_pins[HHKB_COL_BIT2_PIN]);
    setPinOutput(HHKB_pins[HHKB_COL_SELECT_PIN]);
    setPinOutput(HHKB_pins[HHKB_KEY_PREV_PIN]);
#ifdef HHKB_POWER_SAVING
    setPinOutput(HHKB_pins[HHKB_POWER_PIN]);
#endif
#ifdef HHKB_JP
    setPinOutput(HHKB_pins[HHKB_JP_COL_BIT3]);
    setPinOutput(HHKB_pins[HHKB_JP_COL_BIT4]);
#endif
    KEY_UNABLE();
    KEY_PREV_OFF();
    KEY_POWER_OFF();
}

#define SET_PIN_COND(PIN, COND) if (COND) writePinHigh(PIN); else writePinLow(PIN);

static inline void KEY_SELECT(uint8_t ROW, uint8_t COL)
{
    SET_PIN_COND(HHKB_pins[HHKB_ROW_BIT0_PIN], ROW & 1);
    SET_PIN_COND(HHKB_pins[HHKB_ROW_BIT1_PIN], ROW & 2);
    SET_PIN_COND(HHKB_pins[HHKB_ROW_BIT2_PIN], ROW & 4);

    SET_PIN_COND(HHKB_pins[HHKB_COL_BIT0_PIN], COL & 1);
    SET_PIN_COND(HHKB_pins[HHKB_COL_BIT1_PIN], COL & 2);
    SET_PIN_COND(HHKB_pins[HHKB_COL_BIT2_PIN], COL & 4);
}

#endif
