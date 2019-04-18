#include "matrix.h"
#include "nrf.h"
#include "app_ble_func.h"

#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_log.h"

extern void led_init_kb(void);

void matrix_init_user() {
  set_usb_enabled(true);

  // blink on power on
  nrf_gpio_cfg_output(LED_PIN);
  nrf_gpio_cfg_output(BACKLIGHT_PIN);

  for (int i = 0; i < 3; i++) {
    nrf_gpio_pin_set(LED_PIN);
    nrf_gpio_pin_set(BACKLIGHT_PIN);
    nrf_delay_ms(100);

    nrf_gpio_pin_clear(LED_PIN);
    nrf_gpio_pin_clear(BACKLIGHT_PIN);
    nrf_delay_ms(100);
  }

  nrf_gpio_pin_set(LED_PIN);

  led_init_kb();
}
