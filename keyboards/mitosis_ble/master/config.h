#ifndef MASTER_CONFIG_H_
#define MASTER_CONFIG_H_

#include "custom_board.h"

#define ENABLE_STARTUP_ADV_NOLIST 1

#define THIS_DEVICE_ROWS 1
#define THIS_DEVICE_COLS 22

#define MATRIX_ROW_PINS { NO_PIN }

#define MATRIX_COL_PINS { S01, S02, S03, S04, S05, S06, S07, S08, S09, S10, \
                          S11, S12, S13, S14, S15, S16, S17, S18, S19, S20, \
                          S21, S22 }

#define IS_LEFT_HAND true

#endif /* MASTER_CONFIG_H_ */
