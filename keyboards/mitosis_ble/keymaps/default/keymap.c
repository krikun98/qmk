#include QMK_KEYBOARD_H
#include "app_ble_func.h"

enum mitosis_layers
{
  _BL,
  _RAISE
};

enum mitosis_keycodes
{
  FNKEY = SAFE_RANGE,
  RAISE
};


#define _______ KC_TRNS
#define XXXXXXX KC_NO
#define DUAL_R  LT(_RAISE,KC_SPC)

// test mitosis-mjt-like qwerty layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_BL] = {

{ KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,
  KC_A,  KC_S,    KC_D,    KC_F,    KC_G,
  KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,
         KC_LALT, KC_ESC,  KC_TAB,  KC_QUOT,
         KC_LCTL, KC_LGUI, KC_SPC,  KC_LSFT },
                                                { KC_Y,    KC_U,    KC_I,    KC_O,     KC_P, 
                                                  KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN,
                                                  KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH,
                                                  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,
                                                  DUAL_R,  KC_BSPC, KC_ENT,  _______ }
},

[_RAISE] = {

{ KC_1,    KC_2,    KC_3,   KC_4,     KC_5,
  KC_F1,   KC_F2,   KC_F3,  KC_F4,    KC_F5,
  KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,
           _______, KC_BRK, KC_CAPS,  KC_GRV,
           _______, _______, _______, _______},
                                                { KC_6,    KC_7,    KC_8,    KC_9,     KC_0,
                                                  KC_F6,   KC_MINS, KC_EQL,  KC_LBRC,  KC_RBRC,
                                                  KC_F12,  KC_BSLS, _______, _______,  KC_QUOT,
                                                  KC_HOME, KC_PGDN, KC_PGUP, KC_END,
                                                  _______, KC_DEL,  KC_PSCR, _______}
}

/*
DUAL_R,  KC_BSPC, KC_ENT,  _______,  XXXXXXX[_BL] = {
  {KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,          KC_Y,    KC_U,    KC_I,    KC_O,     KC_P    },
  {KC_A,    KC_S,    KC_D,    KC_F,    KC_G,          KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN },
  {KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,          KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH },
  {XXXXXXX, KC_LALT, KC_ESC,  KC_TAB,  KC_QUOT,       KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT, XXXXXXX },
  {XXXXXXX, KC_LCTL, KC_LGUI, KC_SPC,  KC_LSFT,       DUAL_R,  KC_BSPC, KC_ENT,  _______,  XXXXXXX }
},
[_RAISE] = {
  {KC_1,    KC_2,    KC_3,   KC_4,     KC_5,          KC_6,    KC_7,    KC_8,    KC_9,     KC_0    },
  {KC_F1,   KC_F2,   KC_F3,  KC_F4,    KC_F5,         KC_F6,   KC_MINS, KC_EQL,  KC_LBRC,  KC_RBRC },
  {KC_F7,   KC_F8,   KC_F9,  KC_F10,   KC_F11,        KC_F12,  KC_BSLS, _______, _______,  KC_QUOT },
  {XXXXXXX, _______, KC_BRK, KC_CAPS,  KC_GRV,        KC_HOME, KC_PGDN, KC_PGUP, KC_END,   XXXXXXX },
  {XXXXXXX, _______, _______, _______, _______,       _______, KC_DEL,  KC_PSCR, _______,  XXXXXXX }
}
*/

};

#include "nrf_log_ctrl.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    NRF_LOG_INFO("process_record_user, keycode: %d\n", keycode);
  }
  return true;
}

