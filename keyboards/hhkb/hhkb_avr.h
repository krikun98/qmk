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

/* #define HHKB_PINS { D7, B7, B0, B1, B2, B3, B4, B5, B6 } */ /* Hasu Alt Controller */
#define HHKB_PINS { D7, F7, B1, B2, B3, B4, B5, B6, F6 } /* Pro Micro default */

enum {
    HHKB_KEY_PIN = 0,
    HHKB_KEY_PREV_PIN,
    HHKB_ROW_BIT0_PIN,
    HHKB_ROW_BIT1_PIN,
    HHKB_ROW_BIT2_PIN,
    HHKB_COL_BIT0_PIN,
    HHKB_COL_BIT1_PIN,
    HHKB_COL_BIT2_PIN,
    HHKB_COL_SELECT_PIN,
    HHKB_PIN_COUNT
} HHKB_pins_enum;

static const pin_t HHKB_pins[HHKB_PIN_COUNT] = HHKB_PINS;

static inline void KEY_ENABLE(void) { writePinLow(HHKB_pins[HHKB_COL_SELECT_PIN]); }
static inline void KEY_UNABLE(void) { writePinHigh(HHKB_pins[HHKB_COL_SELECT_PIN]); }
static inline bool KEY_STATE(void) { return readPin(HHKB_pins[HHKB_KEY_PIN]); }
static inline void KEY_PREV_ON(void) { writePinHigh(HHKB_pins[HHKB_KEY_PREV_PIN]); }
static inline void KEY_PREV_OFF(void) { writePinLow(HHKB_pins[HHKB_KEY_PREV_PIN]); }

static inline void KEY_POWER_ON(void) {}
static inline void KEY_POWER_OFF(void) {}
static inline bool KEY_POWER_STATE(void) { return true; }

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

#elif defined(PRO_MICRO)
/*
 * Pro Micro-based controller (ATMega32U4) and HHKB Pro 2
 *
 * PB0 on ProMicro is occupied by RX LED, so row and col pins are B1-B6
 * PB6 remapped to PF6, PB7 remapped to PF7
 *
 * row:     PB0-2             remapped to B1-3
 * col:     PB3-5,6           remapped to B4-6, F6
 * key:     PD7(pull-uped)    D7 (same)
 * prev:    PB7               remapped to F7
 * power:   PD4(L:off/H:on)   D4 (same)
 * row-ext: PC6,7 for HHKB JP(active low) same (unused)
 */
static inline void KEY_ENABLE(void) { (PORTF &= ~(1<<6)); }
static inline void KEY_UNABLE(void) { (PORTF |=  (1<<6)); }
static inline bool KEY_STATE(void) { return (PIND & (1<<7)); }
static inline void KEY_PREV_ON(void) { (PORTF |=  (1<<7)); }
static inline void KEY_PREV_OFF(void) { (PORTF &= ~(1<<7)); }

static inline void KEY_POWER_ON(void) {}
static inline void KEY_POWER_OFF(void) {}
static inline bool KEY_POWER_STATE(void) { return true; }

static inline void KEY_INIT(void)
{
    /* row,col,prev: output */
    DDRB  = 0xFF;
    PORTB = 0x80;   // unable
    /* key: input with pull-up */
    DDRD  &= ~0x80;
    PORTD |=  0x80;

    DDRF  |= (1<<6|1<<7);
    PORTF |= (1<<6|1<<7);

    KEY_UNABLE();
    KEY_PREV_OFF();

    KEY_POWER_OFF();
}
static inline void KEY_SELECT(uint8_t ROW, uint8_t COL)
{
    PORTB = (PORTB & 0x81) | (((COL) & 0x07)<<4) | (((ROW) & 0x07)<<1);
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
