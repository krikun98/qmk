#include "jian_nrf52832.h"
#include "pin_assign.h"
#include "nrf_gpio.h"

#define setPinOutput nrf_gpio_cfg_output
#define writePinLow nrf_gpio_pin_clear
#define writePinHigh nrf_gpio_pin_set
