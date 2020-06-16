#include "jorne_ble.h"
#include "nrf_gpio.h"
#include "nrf_delay.h"
#include "nrf_power.h"
#include "nrfx_power.h"
#include "nrfx_pwm.h"
#include "nrf.h"
#include "app_ble_func.h"

// adafruit bootloader, send "dfu" to debug serial port
#define DFU_MAGIC_UF2_RESET             0x57
void bootloader_jump(void) {
  sd_power_gpregret_set(0, DFU_MAGIC_UF2_RESET);
  NVIC_SystemReset();
}

bool has_usb(void) {
  return (nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_CONNECTED
    || nrfx_power_usbstatus_get() == NRFX_POWER_USB_STATE_READY);
}

static bool ble_flag = false;

void nrfmicro_power_enable(bool enable) {
//  if (has_usb()) enable = true;
#ifdef USE_POWER_PIN_GND
  nrf_gpio_pin_write(POWER_PIN, enable);
#endif
#ifdef USE_POWER_PIN_VCC
  nrf_gpio_pin_write(POWER_PIN, !enable);
#endif
}

uint8_t nrfmicro_switch_pin(void) {
#ifdef USE_SWITCH_PIN
  return nrf_gpio_pin_read(SWITCH_PIN);
#else
  return 1;
#endif
}


void check_ble_switch(bool init) {
  uint8_t value = nrfmicro_switch_pin();

  if (init || ble_flag != value) {
    ble_flag = value;

    // mind that it doesn't disable BLE completely, it only disables send
    set_usb_enabled(!ble_flag);
    set_ble_enabled(ble_flag);

    nrf_gpio_pin_clear(LED_PIN);

    if (ble_flag) {
      // blink twice on ble enabled
      for (int i=0; i<2; i++) {
        nrf_gpio_pin_set(LED_PIN);
        nrf_delay_ms(100);
        nrf_gpio_pin_clear(LED_PIN);
        nrf_delay_ms(100);
      }
    }
  }
}

void nrfmicro_init(void) {
  nrf_gpio_cfg_output(LED_PIN);

#ifdef USE_POWER_PIN
  nrf_gpio_cfg_output(POWER_PIN);
#endif

#ifdef USE_SWITCH_PIN
  nrf_gpio_cfg_input(SWITCH_PIN, NRF_GPIO_PIN_PULLDOWN);
#endif

#ifdef USE_INTERNAL_LDO
  // set internal LDO to 3.3V (power mosfet can't close at 1.8V)
  if (NRF_UICR->REGOUT0 != UICR_REGOUT0_VOUT_3V3) {
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Wen << NVMC_CONFIG_WEN_Pos;
    NRF_UICR->REGOUT0 = UICR_REGOUT0_VOUT_3V3;
    NRF_NVMC->CONFIG = NVMC_CONFIG_WEN_Ren << NVMC_CONFIG_WEN_Pos;
  }
#endif

#ifdef USE_MCP73811_CTRL
  nrf_gpio_cfg_output(STAT_PIN);
  nrf_gpio_cfg_output(PROG_PIN);
  nrf_gpio_pin_write(STAT_PIN, 1); // 0/1 - disable/enable MCP73811 charger
  nrf_gpio_pin_write(PROG_PIN, 0); // 0 - 85 mA, 1 - 450 mA
#endif

#ifdef USE_MCP73831_CTRL
  nrf_gpio_cfg_input(PROG_PIN, NRF_GPIO_PIN_PULLDOWN); // Rprog = 13K, 1000/13K ~= 78 mA current
#endif

#ifdef USE_TP4054_CTRL
  nrf_gpio_cfg_output(PROG_PIN); // set to input (float) to disable the charger
  nrf_gpio_cfg_write(PROG_PIN, 0); // set prog resistor to GND to enable the charger
#endif

  nrfmicro_power_enable(true);

  check_ble_switch(true);
}

// called every matrix_scan_user
void nrfmicro_update(void) {
  check_ble_switch(false);
}

