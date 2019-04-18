#include "jian_nrf52832.h"
#include "pin_assign.h"
#include "nrf_gpio.h"

#define setPinOutput nrf_gpio_cfg_output
#define writePinLow nrf_gpio_pin_clear
#define writePinHigh nrf_gpio_pin_set

#define IS_LED_ON(leds, led_name)   ( (leds) & (1 << (led_name)))
#define IS_LED_OFF(leds, led_name)  (~(leds) & (1 << (led_name)))

#ifdef PHYSICAL_LEDS_ENABLE
void led_init_kb(void)
{
#ifdef NUM_LOCK_LED_PIN
    setPinOutput(NUM_LOCK_LED_PIN);
    RESET_NUM_LOCK_LED();
#endif // NUM_LOCK_LED_PIN
#ifdef CAPS_LOCK_LED_PIN
    setPinOutput(CAPS_LOCK_LED_PIN);
    RESET_CAPS_LOCK_LED();
#endif // CAPS_LOCK_LED_PIN
#ifdef SCROLL_LOCK_LED_PIN
    setPinOutput(SCROLL_LOCK_LED_PIN);
    RESET_SCROLL_LOCK_LED();
#endif // SCROLL_LOCK_LED_PIN
}
#endif // PHYSICAL_LEDS_ENABLE

void matrix_init_kb(void) {
#ifdef PHYSICAL_LEDS_ENABLE
  led_init_kb();
#endif // PHYSICAL_LEDS_ENABLE
  matrix_init_user();
};

#ifdef PHYSICAL_LEDS_ENABLE
void led_set_kb(uint8_t usb_led)
{
    NRF_LOG_INFO("leds: %d", usb_led);

#ifdef NUM_LOCK_LED_PIN
   if (IS_LED_ON(usb_led, USB_LED_NUM_LOCK)) {
        SET_NUM_LOCK_LED();
    } else {
        RESET_NUM_LOCK_LED();
    }
#endif // NUM_LOCK_LED_PIN
#ifdef CAPS_LOCK_LED_PIN
    if (IS_LED_ON(usb_led, USB_LED_CAPS_LOCK)) {
        SET_CAPS_LOCK_LED();
    } else {
        RESET_CAPS_LOCK_LED();
    }
#endif // CAPS_LOCK_LED_PIN
#ifdef SCROLL_LOCK_LED_PIN
    if (IS_LED_ON(usb_led, USB_LED_SCROLL_LOCK)) {
        SET_SCROLL_LOCK_LED();
    } else {
        RESET_SCROLL_LOCK_LED();
    }
#endif // SCROLL_LOCK_LED_PIN

    led_set_user(usb_led);

}
#endif // PHYSICAL_LEDS_ENABLE

