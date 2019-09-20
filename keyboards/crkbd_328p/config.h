/*
Copyright 2019 Takuya Urakawa (dm9records.com)

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

#pragma once

#include "config_common.h"

/* USB Device descriptor parameter */
/* VID & PID from vusb project, see tmk_core/protocol/vusb/USB-IDs-for-free.txt"*/
#define VENDOR_ID 0x16c0
#define PRODUCT_ID 0x27db
#define DEVICE_VER 0x0002
#define MANUFACTURER joric
#define PRODUCT crkbd_328p
#define DESCRIPTION crkbd_328p

/* key matrix size */
#define MATRIX_ROWS 8
#define MATRIX_COLS 6

// sadly B5 cannot be used as input on pro mini
// B5 (pin13) is a built-in LED with load resistor

#define MATRIX_ROW_PINS { D4, D5, D6, D7 }
#define MATRIX_COL_PINS { C3, C2, C1, C0, B5, B4 }
#define UNUSED_PINS

/* COL2ROW, ROW2COL*/
#define DIODE_DIRECTION COL2ROW
//#define NO_UART 1
#define VUSB_DISABLE 1


