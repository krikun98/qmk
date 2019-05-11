#ifndef HHKB_AVR_H
#define HHKB_AVR_H

#include <stdint.h>
#include <stdbool.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <quantum.h>


// Timer resolution check
#if (1000000/TIMER_RAW_FREQ > 20)
#   error "Timer resolution(>20us) is not enough for HHKB matrix scan tweak on V-USB."
#endif


/*
 * HHKB Matrix I/O
 *
 * row:     HC4051[A,B,C]  selects scan row0-7
 * row-ext: [En0,En1] row extention for JP
 * col:     LS145[A,B,C,D] selects scan col0-7 and enable(D)
 * key:     on: 0/off: 1
 * prev:    hysteresis control: assert(1) when previous key state is on
 */

#if defined(CUSTOM_BOARD)

#define HHKB_PINS_HASU           { D7, B7, B0, B1, B2, B3, B4, B5, B6, D4 }
#define HHKB_PINS_HASU_JP        { D7, B7, B0, B1, B2, B3, B4, B5, B6, D4, C6, C7 }
#define HHKB_PINS_HBAR           { B2, B3, D7, B1, C6, F7, D4, F6, F5 }

#define HHKB_PINS HHKB_PINS_HBAR
//#define HHKB_POWER_SAVING

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

static const pin_t HHKB_pins[HHKB_PINS_COUNT] = HHKB_PINS;

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

#elif defined(__AVR_ATmega32U4__)
/*
 * For TMK HHKB alt controller(ATMega32U4)
 *
 * row:     PB0-2
 * col:     PB3-5,6
 * key:     PD7(pull-uped)
 * prev:    PB7
 * power:   PD4(L:off/H:on)
 * row-ext: PC6,7 for HHKB JP(active low)
 */
static inline void KEY_ENABLE(void) { (PORTB &= ~(1<<6)); }
static inline void KEY_UNABLE(void) { (PORTB |=  (1<<6)); }
static inline bool KEY_STATE(void) { return (PIND & (1<<7)); }
static inline void KEY_PREV_ON(void) { (PORTB |=  (1<<7)); }
static inline void KEY_PREV_OFF(void) { (PORTB &= ~(1<<7)); }
#ifdef HHKB_POWER_SAVING
static inline void KEY_POWER_ON(void) {
    DDRB = 0xFF; PORTB = 0x40;          // change pins output
    DDRD |= (1<<4); PORTD |= (1<<4);    // MOS FET switch on
    /* Without this wait you will miss or get false key events. */
    _delay_ms(5);                       // wait for powering up
}
static inline void KEY_POWER_OFF(void) {
    /* input with pull-up consumes less than without it when pin is open. */
    DDRB = 0x00; PORTB = 0xFF;          // change pins input with pull-up
    DDRD |= (1<<4); PORTD &= ~(1<<4);   // MOS FET switch off
}
static inline bool KEY_POWER_STATE(void) { return PORTD & (1<<4); }
#else
static inline void KEY_POWER_ON(void) {}
static inline void KEY_POWER_OFF(void) {}
static inline bool KEY_POWER_STATE(void) { return true; }
#endif
static inline void KEY_INIT(void)
{
    /* row,col,prev: output */
    DDRB  = 0xFF;
    PORTB = 0x40;   // unable
    /* key: input with pull-up */
    DDRD  &= ~0x80;
    PORTD |=  0x80;
#ifdef HHKB_JP
    /* row extention for HHKB JP */
    DDRC  |= (1<<6|1<<7);
    PORTC |= (1<<6|1<<7);
#endif
    KEY_UNABLE();
    KEY_PREV_OFF();

    KEY_POWER_OFF();
}
static inline void KEY_SELECT(uint8_t ROW, uint8_t COL)
{
    PORTB = (PORTB & 0xC0) | (((COL) & 0x07)<<3) | ((ROW) & 0x07);
#ifdef HHKB_JP
    if ((ROW) & 0x08) PORTC = (PORTC & ~(1<<6|1<<7)) | (1<<6);
    else              PORTC = (PORTC & ~(1<<6|1<<7)) | (1<<7);
#endif
}


#elif defined(__AVR_AT90USB1286__)
/*
 * For Teensy++(AT90USB1286)
 *
 *                          HHKB pro    HHKB pro2
 * row:     PB0-2           (6-8)       (5-7)
 * col:     PB3-5,6         (9-12)      (8-11)
 * key:     PE6(pull-uped)  (4)         (3)
 * prev:    PE7             (5)         (4)
 *
 * TODO: convert into 'staitc inline' function
 */
#define KEY_INIT()              do {    \
    DDRB |= 0x7F;                       \
    DDRE |=  (1<<7);                    \
    DDRE &= ~(1<<6);                    \
    PORTE |= (1<<6);                    \
} while (0)
#define KEY_SELECT(ROW, COL)    (PORTB = (PORTB & 0xC0) |       \
                                         (((COL) & 0x07)<<3) |  \
                                         ((ROW) & 0x07))
#define KEY_ENABLE()            (PORTB &= ~(1<<6))
#define KEY_UNABLE()            (PORTB |=  (1<<6))
#define KEY_STATE()             (PINE & (1<<6))
#define KEY_PREV_ON()           (PORTE |=  (1<<7))
#define KEY_PREV_OFF()          (PORTE &= ~(1<<7))
#define KEY_POWER_ON()
#define KEY_POWER_OFF()
#define KEY_POWER_STATE()       true


#else
#   error "define code for matrix scan"
#endif


#if 0
// For ATMega328P with V-USB
//
// #elif defined(__AVR_ATmega328P__)
// Ports for V-USB
// key:     PB0(pull-uped)
// prev:    PB1
// row:     PB2-4
// col:     PC0-2,3
// power:   PB5(Low:on/Hi-z:off)
#define KEY_INIT()              do {    \
    DDRB  |= 0x3E;                      \
    DDRB  &= ~(1<<0);                   \
    PORTB |= 1<<0;                      \
    DDRC  |= 0x0F;                      \
    KEY_UNABLE();                       \
    KEY_PREV_OFF();                     \
} while (0)
#define KEY_SELECT(ROW, COL)    do {    \
    PORTB = (PORTB & 0xE3) | ((ROW) & 0x07)<<2; \
    PORTC = (PORTC & 0xF8) | ((COL) & 0x07);    \
} while (0)
#define KEY_ENABLE()            (PORTC &= ~(1<<3))
#define KEY_UNABLE()            (PORTC |=  (1<<3))
#define KEY_STATE()             (PINB & (1<<0))
#define KEY_PREV_ON()           (PORTB |=  (1<<1))
#define KEY_PREV_OFF()          (PORTB &= ~(1<<1))
// Power supply switching
#define KEY_POWER_ON()          do {    \
    KEY_INIT();                         \
    PORTB &= ~(1<<5);                   \
    _delay_ms(1);                       \
} while (0)
#define KEY_POWER_OFF()         do {    \
    DDRB  &= ~0x3F;                     \
    PORTB &= ~0x3F;                     \
    DDRC  &= ~0x0F;                     \
    PORTC &= ~0x0F;                     \
} while (0)
#endif

#endif
