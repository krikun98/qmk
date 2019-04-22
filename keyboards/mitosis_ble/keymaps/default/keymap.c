/*
Copyright 2018 Sekigon

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H
#include "app_ble_func.h"

extern keymap_config_t keymap_config;

enum jian_layers {
  _QWERTY,
  _ISO,
  _LOWER,
  _RAISE,
  _ADJUST,
  _THUMB_ALT,
};

enum custom_keycodes {
  AD_WO_L = SAFE_RANGE, /* Start advertising without whitelist  */
  BLE_DIS,              /* Disable BLE HID sending              */
  BLE_EN,               /* Enable BLE HID sending               */
  USB_DIS,              /* Disable USB HID sending              */
  USB_EN,               /* Enable USB HID sending               */
  DELBNDS,              /* Delete all bonding                   */
  ADV_ID0,              /* Start advertising to PeerID 0        */
  ADV_ID1,              /* Start advertising to PeerID 1        */
  ADV_ID2,              /* Start advertising to PeerID 2        */
  ADV_ID3,              /* Start advertising to PeerID 3        */
  ADV_ID4,              /* Start advertising to PeerID 4        */
  BATT_LV,              /* Display battery level in milli volts */
  DEL_ID0,              /* Delete bonding of PeerID 0           */
  DEL_ID1,              /* Delete bonding of PeerID 1           */
  DEL_ID2,              /* Delete bonding of PeerID 2           */
  DEL_ID3,              /* Delete bonding of PeerID 3           */
  DEL_ID4,              /* Delete bonding of PeerID 4           */
  ENT_DFU,              /* Start bootloader                     */
  ENT_SLP,              /* Deep sleep mode                      */

  // jian keycodes
  QWERTY,
  PLOVER,
  EXT_PLV,
  SH_TG, // not implemented
  BLE_DBG
};



#define _______ KC_TRNS
#define XXXXXXX KC_NO

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)

#define TG_ISO  TG(_ISO)
#define TG_THMB TG(_THUMB_ALT)

#define RBR_RGU MT(MOD_RGUI, KC_RBRC)
#define F12_RGU MT(MOD_RGUI, KC_F12)
#define PLS_LCT MT(MOD_LCTL, KC_PPLS)
#define EQL_LCT MT(MOD_LCTL, KC_PEQL)
#define APP_LCT MT(MOD_LCTL, KC_APP)
#define EQL_RCT MT(MOD_RCTL, KC_PEQL)
#define QUO_RCT MT(MOD_RCTL, KC_QUOT)
#define APP_RCT MT(MOD_RCTL, KC_APP)
#define MIN_RCT MT(MOD_RCTL, KC_MINS)
#define EQL_LAL MT(MOD_LALT, KC_EQL)
#define BSL_RAL MT(MOD_RALT, KC_BSLS)

#define NBS_LCT MT(MOD_LCTL, KC_NUBS)
#define BSH_LAL MT(MOD_LALT, KC_BSLS)
#define APP_RAL MT(MOD_RALT, KC_APP)

#define BSP_LSH MT(MOD_LSFT, KC_BSPC)
#define SPC_RSH MT(MOD_RSFT, KC_SPC)
#define DEL_RSE LT(_RAISE, KC_DEL)
#define TAB_RSE LT(_RAISE, KC_TAB)
#define ENT_LWR LT(_LOWER, KC_ENT)
#define ESC_LWR LT(_LOWER, KC_ESC)

#define LAYOUT_base( \
    GRV, Q, W, E, R, T, Y, U, I,    O,   P,    LBRC, RBRC, \
         A, S, D, F, G, H, J, K,    L,   SCLN, QUOT, \
         Z, X, C, V, B, N, M, COMM, DOT, SLSH \
  ) \
  LAYOUT( \
  KC_LGUI, GRV,     Q,       W,       E,       R,       T,            Y,       U,       I,       O,       P,       LBRC,    RGUI_T(RBRC), \
           KC_LCTL, A,       S,       D,       F,       G,            H,       J,       K,       L,       SCLN,    RCTL_T(QUOT), \
           KC_LALT, Z,       X,       C,       V,       B,            N,       M,       COMM,    DOT,     SLSH,    BSL_RAL, \
                                      TAB_RSE, SPC_RSH, ENT_LWR,      ESC_LWR, BSP_LSH, DEL_RSE \
  )
#define LAYOUT_base_wrapper(...) LAYOUT_base(__VA_ARGS__)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

[_QWERTY] = LAYOUT_base_wrapper(QWERTY_base),

[_LOWER] = LAYOUT(\
  _______, KC_UNDS, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  F12_RGU, \
           PLS_LCT, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,      KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, MIN_RCT, \
           EQL_LAL, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
                                      _______, _______, _______,      _______, _______, _______\
),

[_RAISE] = LAYOUT(\
  _______, KC_NLCK, KC_PSLS, KC_P7,   KC_P8,   KC_P9,   KC_PMNS,      KC_VOLU, KC_HOME, KC_PSCR, KC_PGUP, KC_SLCK, KC_CAPS, _______, \
           EQL_LCT, KC_PAST, KC_P4,   KC_P5,   KC_P6,   KC_PPLS,      KC_MUTE, KC_LEFT, KC_UP,   KC_RGHT, KC_INS,  APP_RCT, \
           _______, KC_P0,   KC_P1,   KC_P2,   KC_P3,   KC_PCMM,      KC_VOLD, KC_END,  KC_DOWN, KC_PGDN, KC_PAUS, _______, \
                                      _______, _______, _______,      _______, _______, _______\
),

[_ADJUST] = LAYOUT(\
    RESET, DEBUG,   KC_ASUP, XXXXXXX, XXXXXXX, DELBNDS, AD_WO_L,      AD_WO_L, DELBNDS, XXXXXXX, XXXXXXX,  KC_ASUP, DEBUG,   RESET, \
           DEL_ID0, DEL_ID1, DEL_ID2, DEL_ID3, USB_DIS, USB_EN,       USB_EN,  USB_DIS,  DEL_ID3, DEL_ID2, DEL_ID1, DEL_ID0, \
           ADV_ID0, ADV_ID1, ADV_ID2, ADV_ID3, BLE_DIS, BLE_EN,       BLE_EN,  BLE_DIS,  ADV_ID3, ADV_ID2, ADV_ID1, ADV_ID0, \
                                      _______, SH_TG,   _______,      _______, SH_TG,   _______\
)

};

uint32_t layer_state_set_user(uint32_t state) {
  return update_tri_layer_state(state, _LOWER, _RAISE, _ADJUST);
}


char keycode_to_char(uint16_t keycode) {
const char code_to_name[60] = {
    ' ', ' ', ' ', ' ', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p',
    'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
    '1', '2', '3', '4', '5', '6', '7', '8', '9', '0',
    'R', 'E', 'B', 'T', ' ', ' ', ' ', ' ', ' ', ' ',
    ' ', ';', '\'', ' ', ',', '.', '/', ' ', ' ', ' '};

  char name = ' ';
  if (keycode < 60) {
    name = code_to_name[keycode];
  }
  return name;
}


#include "nrf_log.h"

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  //char str[16];
  if (record->event.pressed) {

    NRF_LOG_INFO("process_record_user, keycode: %d, char: %c\n", keycode, keycode_to_char(keycode));

    switch (keycode) {
    case DELBNDS:
      delete_bonds();
      return false;
    case AD_WO_L:
      restart_advertising_wo_whitelist();
      return false;
    case USB_EN:
      set_usb_enabled(true);
      return false;
      break;
    case USB_DIS:
      set_usb_enabled(false);
      return false;
      break;
    case BLE_EN:
      set_ble_enabled(true);
      return false;
      break;
    case BLE_DIS:
      set_ble_enabled(false);
      return false;
      break;
    case ADV_ID0:
      restart_advertising_id(0);
      return false;
    case ADV_ID1:
      restart_advertising_id(1);
      return false;
    case ADV_ID2:
      restart_advertising_id(2);
      return false;
    case ADV_ID3:
      restart_advertising_id(3);
      return false;
    case ADV_ID4:
      restart_advertising_id(4);
      return false;
    case DEL_ID0:
      delete_bond_id(0);
      return false;
    case DEL_ID1:
      delete_bond_id(1);
      return false;
    case DEL_ID2:
      delete_bond_id(2);
      return false;
    case DEL_ID3:
      delete_bond_id(3);
      return false;
    case BATT_LV:
      //sprintf(str, "%4dmV", get_vcc());
      //send_string(str);
      return false;
    case ENT_DFU: case RESET:
      bootloader_jump();
      return false;
    case DEBUG:
      //uf2_jump();
      return false;
    case BLE_DBG:
      set_ble_enabled(true);
      //delete_bonds(); // causes reset
      restart_advertising_wo_whitelist();
      return false;
    }
  }
  else if (!record->event.pressed) {
    switch (keycode) {
    case ENT_SLP:
      sleep_mode_enter();
      return false;
    }

  }
  return true;
}
;
