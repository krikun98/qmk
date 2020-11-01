#ifndef JIAN_BLE_H_
#define JIAN_BLE_H_

#include "quantum.h"

// Used to create a keymap using only KC_ prefixed keys
#define XXX KC_NO
#define ___ KC_TRNS
#define LAYOUT( \
  L20, L00, L01, L12, L02, L03, L04,    R04, R03, R02, R12, R01, R00, R20, \
       L10, L11, L22, L13, L14, L05,    R05, R14, R13, R22, R11, R10, \
       L21, L32, L33, L23, L24, L15,    R15, R24, R23, R33, R32, R21, \
                      L34, L25, L35,    R35, R25, R34 \
) \
{ \
  {L00, L01, L02, L03, L04, L05 }, \
  {L10, L11, L12, L13, L14, L15 }, \
  {L20, L21, L22, L23, L24, L25 }, \
  {XXX, XXX, L32, L33, L34, L35 }, \
  {R00, R01, R02, R03, R04, R05 }, \
  {R10, R11, R12, R13, R14, R15 }, \
  {R20, R21, R22, R23, R24, R25 }, \
  {XXX, XXX, R32, R33, R34, R35 }  \
}


#define LAYOUT_kc_jian LAYOUT_kc

#define QWERTY_base  KC_GRV, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U, KC_I,    KC_O,   KC_P,    KC_LBRC, KC_RBRC, \
                             KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J, KC_K,    KC_L,   KC_SCLN, KC_QUOT, \
                             KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M, KC_COMM, KC_DOT, KC_SLSH

#endif /* JIAN_BLE_H_ */
