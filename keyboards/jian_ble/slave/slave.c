
#include "matrix.h"

#include "wait.h"
#include "app_ble_func.h"
#include "bootloader.h"

#include "nrf_power.h"
#include "nrf.h"


#include "nrf_gpio.h"
#include "nrf_delay.h"


void unselect_rows(void);
void select_row(uint8_t row);
matrix_row_t read_cols(void);

static bool bootloader_flag = false;

void matrix_init_user() {
  //set_usb_enabled(true);

  // blink on power on
  nrf_gpio_cfg_output(LED_PIN);
  nrf_gpio_cfg_output(BACKLIGHT_PIN);

  for (int i = 0; i < 2; i++) {
    nrf_gpio_pin_set(LED_PIN);
    nrf_gpio_pin_set(BACKLIGHT_PIN);
    nrf_delay_ms(100);

    nrf_gpio_pin_clear(LED_PIN);
    nrf_gpio_pin_clear(BACKLIGHT_PIN);
    nrf_delay_ms(100);
  }

  select_row(0);
  wait_us(50);
  matrix_row_t row = read_cols();
  unselect_rows();

  if (row == 0b11100) {
    delete_bonds();
  } else if (row == 0b10) {
    bootloader_flag = true;
  }
}

void matrix_scan_user() {
  static int cnt;
  if (bootloader_flag && cnt++==500) {
    bootloader_jump();
  }
}
