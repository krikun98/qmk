#ifndef RGBLIGHT_H
#define RGBLIGHT_H

#include "neopixel.h"
#include "neopixel.c"
#include "quantum.h"

neopixel_strip_t m_strip;
uint8_t dig_pin_num = RGB_DI_PIN;
uint8_t leds_per_strip = RGBLED_NUM;

void rgblight_mode(int mode) {
    neopixel_init(&m_strip, dig_pin_num, leds_per_strip);
    neopixel_clear(&m_strip);

    uint8_t r,g,b,a=255;

    for (int j=0; j<4; j++) {

        switch(j) {
            case 0: r=a,g=0,b=0; break;
            case 1: r=0,g=a,b=0; break;
            case 2: r=0,g=0,b=a; break;
            case 3: r=0,g=0,b=0; break;
        }

        for (int i=0; i<leds_per_strip; i++) {
            neopixel_set_color_and_show(&m_strip, i, r, g, b);
            nrf_delay_ms(25);
        }
    }
}

#endif //RGBLIGHT_H
