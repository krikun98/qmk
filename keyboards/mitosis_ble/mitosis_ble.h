#ifndef MITOSIS_BLE_H_
#define MITOSIS_BLE_H_

#include "quantum.h"

// Used to create a keymap using only KC_ prefixed keys
#define XXX KC_NO
#define ___ KC_TRNS
#define LAYOUT( \
  L22, L19, L05, L04, L03, L02, L01,    R01, R02, R03, R04, R05, R19, R22, \
       L20, L10, L09, L08, L07, L06,    R06, R07, R08, R09, R10, R20, \
       L21, L15, L14, L13, L12, L11,    R11, R12, R13, R14, R15, R21, \
                      L17, L16, L18,    R18, R16, R17 \
) \
{ \
    { L01, L02, L03, L04, L05, L06, L07, L08, L09, L10, L11, \
        L12, L13, L14, L15, L16, L17, L18, L19, L20, L21, L22 }, \
    { R01, R02, R03, R04, R05, R06, R07, R08, R09, R10, R11, \
        R12, R13, R14, R15, R16, R17, R18, R19, R20, R21, R22 } \
}

#define LAYOUT_kc_jian LAYOUT_kc

#define QWERTY_base  KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, \
                             KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
                             KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

#endif /* MITOSIS_BLE_H_ */
