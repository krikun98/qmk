/*
 * rev1.c
 *
 *  Created on: 2019/05/12
 *      Author: Joric
 */

#include "matrix.h"
#include "quantum.h"
#include "nrf.h"
#include "app_ble_func.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"

void matrix_init_user() {
  set_usb_enabled(true);

  // blink on power on
  nrf_gpio_cfg_output(LED_PIN);

  for (int i = 0; i < 5; i++) {
    nrf_gpio_pin_set(LED_PIN);
    nrf_delay_ms(100);

    nrf_gpio_pin_clear(LED_PIN);
    nrf_delay_ms(100);
  }

  nrf_gpio_pin_set(LED_PIN);

}

