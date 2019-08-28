/* 
    HHKB / nRFMicro controller by Joric
    define CUSTOM_CUSTOM_MATRIX in makefile to skip nrf52 custom matrix.c
    we only need exposed matrix_get_row for the matrix and that's it
*/


/*
Copyright 2011 Jun Wako <wakojun@gmail.com>

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

/*
 * scan matrix
 */
#include <stdint.h>
#include <stdbool.h>
#include "print.h"
#include "debug.h"
#include "util.h"
#include "timer.h"
#include "matrix.h"
#include "hhkb_avr.h"
#include "suspend.h"

// rtc0 counter is 32k per second, resolution is about 30 us
#define TIMER_RAW_FREQ      (32768)
#define TIMER_RAW           NRF_RTC0->COUNTER

// matrix power saving
#define MATRIX_POWER_SAVE       10000
static uint32_t matrix_last_modified = 0;

// required in "sleep_mode_enter" set all pins to 0 for now
const uint32_t row_pins[THIS_DEVICE_ROWS] = MATRIX_ROW_PINS;
const uint32_t col_pins[THIS_DEVICE_COLS] = MATRIX_COL_PINS;

// matrix state buffer(1:on, 0:off)
static matrix_row_t *matrix;
static matrix_row_t *matrix_prev;
static matrix_row_t _matrix0[MATRIX_ROWS];
static matrix_row_t _matrix1[MATRIX_ROWS];

inline
uint8_t matrix_rows(void)
{
    return MATRIX_ROWS;
}

inline
uint8_t matrix_cols(void)
{
    return MATRIX_COLS;
}

void matrix_init(void)
{
#ifdef DEBUG
    debug_enable = true;
    debug_keyboard = true;
#endif

    KEY_INIT();

    // initialize matrix state: all keys off
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix0[i] = 0x00;
    for (uint8_t i=0; i < MATRIX_ROWS; i++) _matrix1[i] = 0x00;
    matrix = _matrix0;
    matrix_prev = _matrix1;

    matrix_init_user();
}

__attribute__ ((weak))
void matrix_scan_user(void) {
}

void matrix_scan_kb(void) {
  matrix_scan_user();
}
/*
HHKB switch matrix is ghost-free and bounce-free.

    Pro/Pro2(8x8):
      COL 0     1       2       3       4       5       6       7
    ROW ---------------------------------------------------------------
      0|  2     q       w       s       a       z       x       c
      1|  3     4       r       e       d       f       v       b
      2|  5     6       y       t       g       h       n       _NONE_
      3|  1     Esc     Tab     Control LShift  LAlt    LMeta   Space
      4|  7     8       u       i       k       j       m       _NONE_
      5|  \     `       Delete  Return  Fn      RShift  RAlt    RMeta
      6|  9     0       o       p       ;       l       ,       _NONE_
      7|  -     +       ]       [       '       /       .       _NONE_
*/

uint8_t matrix_scan(void)
{
    uint8_t *tmp;

    tmp = matrix_prev;
    matrix_prev = matrix;
    matrix = tmp;

    // power on
    //if (!KEY_POWER_STATE()) KEY_POWER_ON();

//    uint8_t region;
//    sd_nvic_critical_region_enter(&region);

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
        for (uint8_t col = 0; col < MATRIX_COLS; col++) {
            KEY_SELECT(row, col);
            _delay_us(5);

            // Not sure this is needed. This just emulates HHKB controller's behaviour.
            if (matrix_prev[row] & (1<<col)) {
                KEY_PREV_ON();
            }
            _delay_us(10);

            // NOTE: KEY_STATE is valid only in 20us after KEY_ENABLE.
            // If V-USB interrupts in this section we could lose 40us or so
            // and would read invalid value from KEY_STATE.

            //uint8_t last = TIMER_RAW;
            uint32_t last = NRF_RTC0->COUNTER;

            KEY_ENABLE();

            // Wait for KEY_STATE outputs its value.
            // 1us was ok on one HHKB, but not worked on another.
            // no   wait doesn't work on Teensy++ with pro(1us works)
            // no   wait does    work on tmk PCB(8MHz) with pro2
            // 1us  wait does    work on both of above
            // 1us  wait doesn't work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz)
            // 5us  wait does    work on tmk(16MHz/2)
            // 5us  wait does    work on tmk(8MHz)
            // 10us wait does    work on Teensy++ with pro
            // 10us wait does    work on 328p+iwrap with pro
            // 10us wait doesn't work on tmk PCB(8MHz) with pro2(very lagged scan)
            _delay_us(5); // originally 5

            if (KEY_STATE()) {
                matrix[row] &= ~(1<<col);
            } else {
                matrix[row] |= (1<<col);
            }


            if (col==0 && row==0)
                matrix[row] &= ~(1<<col);


            // Ignore if this code region execution time elapses more than 20us.
            // MEMO: 20[us] * (TIMER_RAW_FREQ / 1000000)[count per us]
            // MEMO: then change above using this rule: a/(b/c) = a*1/(b/c) = a*(c/b)
            //if (TIMER_DIFF_RAW(TIMER_RAW, last) > 20/(1000000/TIMER_RAW_FREQ)) {

            if (NRF_RTC0->COUNTER > last) { // at 32k ticks a second 1 tick is about 30 us
                //matrix[row] = matrix_prev[row]; // looks like it just messes everything up
            }

            _delay_us(5); // originally 5
            KEY_PREV_OFF();
            KEY_UNABLE();

            // NOTE: KEY_STATE keep its state in 20us after KEY_ENABLE.
            // This takes 25us or more to make sure KEY_STATE returns to idle state.
#ifdef HHKB_JP
            // Looks like JP needs faster scan due to its twice larger matrix
            // or it can drop keys in fast key typing
            _delay_us(30);
#else
            _delay_us(75); //originally 75
#endif
        }
        if (matrix[row] ^ matrix_prev[row]) matrix_last_modified = timer_read32();
    }

//    sd_nvic_critical_region_exit(region);

/*
    // power off
    if (KEY_POWER_STATE() &&
            (USB_DeviceState == DEVICE_STATE_Suspended ||
             USB_DeviceState == DEVICE_STATE_Unattached ) &&
            timer_elapsed32(matrix_last_modified) > MATRIX_POWER_SAVE) {
        KEY_POWER_OFF();
        suspend_power_down();
    }
*/

    matrix_scan_quantum();

    //NRF_LOG_INFO("rtc: %d", TIMER_RAW/32768); // 32k a second

    return 1;
}

bool matrix_is_modified(void)
{
    for (uint8_t i = 0; i < MATRIX_ROWS; i++) {
        if (matrix[i] != matrix_prev[i])
            return true;
    }
    return false;
}

inline
bool matrix_has_ghost(void)
{
    return false;
}

inline
bool matrix_is_on(uint8_t row, uint8_t col)
{
    return (matrix[row] & (1<<col));
}

inline
matrix_row_t matrix_get_row(uint8_t row)
{
    return matrix[row];
}

void matrix_print(void)
{
    print("\nr/c 01234567\n");
    for (uint8_t row = 0; row < matrix_rows(); row++) {
        xprintf("%02X: %08b\n", row, bitrev(matrix_get_row(row)));
    }
}

uint8_t matrix_key_count(void) {
    uint8_t count = 0;
    for (int8_t r = MATRIX_ROWS - 1; r >= 0; --r) {
        count += bitpop16(matrix_get_row(r));
    }
    return count;
}

void matrix_power_up(void) {
    KEY_POWER_ON();
}
void matrix_power_down(void) {
    KEY_POWER_OFF();
}
