#pragma once

#include "custom_board.h"

#undef B0
#undef B1
#undef B2
#undef B3
#undef B4
#undef B5
#undef B6
#undef C6
#undef D0
#undef D1
#undef D2
#undef D3
#undef D4
#undef D7
#undef E6
#undef F4
#undef F5
#undef F6
#undef F7

#if (IS_LEFT_HAND)
#define FLIPPED_NRFMICRO //flipped nRFMicro 0.03 for master
#endif

#ifdef FLIPPED_NRFMICRO

#define D3 PIN1
#define D2 PIN2
#define F4 PIN5
#define F5 PIN6
#define F6 PIN7
#define F7 PIN8
#define B1 PIN9
#define B3 PIN10
#define B2 PIN11
#define B6 PIN12
#define B5 PIN13
#define B4 PIN14
#define E6 PIN15
#define D7 PIN16
#define C6 PIN17
#define D4 PIN18
#define D0 PIN19
#define D1 PIN20

#else // regular board

#define D3 PIN1
#define D2 PIN2
#define D1 PIN5
#define D0 PIN6
#define D4 PIN7
#define C6 PIN8
#define D7 PIN9
#define E6 PIN10
#define B4 PIN11
#define B5 PIN12
#define B6 PIN13
#define B2 PIN14
#define B3 PIN15
#define B1 PIN16
#define F7 PIN17
#define F6 PIN18
#define F5 PIN19
#define F4 PIN20

#endif

#define THIS_DEVICE_ROWS 4
#define THIS_DEVICE_COLS 7

#define MATRIX_ROW_PINS { D3, D2, E6, B4 }
#define MATRIX_COL_PINS { F4, F5, F6, F7, B1, B3, B2 }
