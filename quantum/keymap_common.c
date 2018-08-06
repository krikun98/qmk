/*
Copyright 2012-2017 Jun Wako <wakojun@gmail.com>

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

#include "keymap.h"
#include "report.h"
#include "keycode.h"
#include "action_layer.h"
#if defined(__AVR__)
#include <util/delay.h>
#include <stdio.h>
#endif
#include "action.h"
#include "action_macro.h"
#include "debug.h"
#include "backlight.h"
#include "quantum.h"

#ifdef SPLIT_KEYBOARD
    #include "split_flags.h"
#endif

#ifdef MIDI_ENABLE
	#include "process_midi.h"
#endif

extern keymap_config_t keymap_config;

#include <inttypes.h>

/* converts key to action */
action_t action_for_key(uint8_t layer, keypos_t key)
{
    // 16bit keycodes - important
    uint16_t keycode = keymap_key_to_keycode(layer, key);

    // keycode remapping
    keycode = keycode_config(keycode);

    action_t action;
    uint8_t action_layer, when, mod;

        if (keycode>=KC_FN0 && keycode<=KC_FN31)
            action.code = keymap_function_id_to_action(FN_INDEX(keycode));
        else
        if ((keycode>=KC_A && keycode<=KC_EXSEL) || (keycode>=KC_LCTRL && keycode<=KC_RGUI))
            action.code = ACTION_KEY(keycode);
        else
        if (keycode>=KC_SYSTEM_POWER && keycode<=KC_SYSTEM_WAKE)
            action.code = ACTION_USAGE_SYSTEM(KEYCODE2SYSTEM(keycode));
        else
        if (keycode>=KC_AUDIO_MUTE && keycode<=KC_MEDIA_REWIND)
            action.code = ACTION_USAGE_CONSUMER(KEYCODE2CONSUMER(keycode));
        else
        if (keycode>=KC_MS_UP && keycode<=KC_MS_ACCEL2)
            action.code = ACTION_MOUSEKEY(keycode);
        else
        if (keycode>=KC_TRNS)
            action.code = ACTION_TRANSPARENT;
        else
        if (keycode>=QK_MODS && keycode<=QK_MODS_MAX)
            // Has a modifier
            // Split it up
            action.code = ACTION_MODS_KEY(keycode >> 8, keycode & 0xFF); // adds modifier to key
        else
        if (keycode>=QK_FUNCTION && keycode<=QK_FUNCTION_MAX)
            // Is a shortcut for function action_layer, pull last 12bits
            // This means we have 4,096 FN macros at our disposal
            action.code = keymap_function_id_to_action( (int)keycode & 0xFFF );
        else
        if (keycode>=QK_MACRO && keycode<=QK_MACRO_MAX)
            if (keycode & 0x800) // tap macros have upper bit set
                action.code = ACTION_MACRO_TAP(keycode & 0xFF);
            else
                action.code = ACTION_MACRO(keycode & 0xFF);
        else
        if (keycode>=QK_LAYER_TAP && keycode<=QK_LAYER_TAP_MAX)
            action.code = ACTION_LAYER_TAP_KEY((keycode >> 0x8) & 0xF, keycode & 0xFF);
        else
			if (keycode>=QK_TO && keycode<=QK_TO_MAX) {
            // Layer set "GOTO"
            when = (keycode >> 0x4) & 0x3;
            action_layer = keycode & 0xF;
            action.code = ACTION_LAYER_SET(action_layer, when);
			}
        else
			if (keycode>=QK_MOMENTARY && keycode<=QK_MOMENTARY_MAX) {
            // Momentary action_layer
            action_layer = keycode & 0xFF;
            action.code = ACTION_LAYER_MOMENTARY(action_layer);
			}
        else
			if (keycode>=QK_DEF_LAYER && keycode<=QK_DEF_LAYER_MAX) {
            // Set default action_layer
            action_layer = keycode & 0xFF;
            action.code = ACTION_DEFAULT_LAYER_SET(action_layer);
			}
        else
			if (keycode>=QK_TOGGLE_LAYER && keycode<=QK_TOGGLE_LAYER_MAX) {
            // Set toggle
            action_layer = keycode & 0xFF;
            action.code = ACTION_LAYER_TOGGLE(action_layer);
			}
        else
			if (keycode>=QK_ONE_SHOT_LAYER && keycode<=QK_ONE_SHOT_LAYER_MAX) {
            // OSL(action_layer) - One-shot action_layer
            action_layer = keycode & 0xFF;
            action.code = ACTION_LAYER_ONESHOT(action_layer);
			}
        else
			if (keycode>=QK_ONE_SHOT_MOD && keycode<=QK_ONE_SHOT_MOD_MAX) {
            // OSM(mod) - One-shot mod
            mod = keycode & 0xFF;
            action.code = ACTION_MODS_ONESHOT(mod);
			}
        else
        if (keycode>=QK_LAYER_TAP_TOGGLE && keycode<=QK_LAYER_TAP_TOGGLE_MAX)
            action.code = ACTION_LAYER_TAP_TOGGLE(keycode & 0xFF);
        else
			if (keycode>=QK_LAYER_MOD && keycode<=QK_LAYER_MOD_MAX) {
            mod = keycode & 0xF;
            action_layer = (keycode >> 4) & 0xF;
            action.code = ACTION_LAYER_MODS(action_layer, mod);
			}
        else
			if (keycode>=QK_MOD_TAP && keycode<=QK_MOD_TAP_MAX) {
            mod = mod_config((keycode >> 0x8) & 0x1F);
            action.code = ACTION_MODS_TAP_KEY(mod, keycode & 0xFF);
			}

    switch (keycode) {
    #ifdef BACKLIGHT_ENABLE
        case BL_ON:
            action.code = ACTION_BACKLIGHT_ON();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_OFF:
            action.code = ACTION_BACKLIGHT_OFF();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_DEC:
            action.code = ACTION_BACKLIGHT_DECREASE();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_INC:
            action.code = ACTION_BACKLIGHT_INCREASE();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_TOGG:
            action.code = ACTION_BACKLIGHT_TOGGLE();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
        case BL_STEP:
            action.code = ACTION_BACKLIGHT_STEP();
            #ifdef SPLIT_KEYBOARD
                BACKLIT_DIRTY = true;
            #endif
            break;
    #endif
    #ifdef SWAP_HANDS_ENABLE
        case QK_SWAP_HANDS ... QK_SWAP_HANDS_MAX:
            action.code = ACTION(ACT_SWAP_HANDS, keycode & 0xff);
            break;
    #endif

        default:
            action.code = ACTION_NO;
            break;
    }
    return action;
}

#ifdef __ICCARM__
__weak
#else
__attribute__ ((weak))
#endif
const uint16_t PROGMEM fn_actions[] = {
0
};

/* Macro */
#ifdef __ICCARM__
__weak
#else
__attribute__ ((weak))
#endif
const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt)
{
    return MACRO_NONE;
}

/* Function */
__attribute__ ((weak))
void action_function(keyrecord_t *record, uint8_t id, uint8_t opt)
{
}

// translates key to keycode
__attribute__ ((weak))
uint16_t keymap_key_to_keycode(uint8_t layer, keypos_t key)
{
    // Read entire word (16bits)
    return pgm_read_word(&keymaps[(layer)][(key.row)][(key.col)]);
}

// translates function id to action
__attribute__ ((weak))
uint16_t keymap_function_id_to_action( uint16_t function_id )
{
    // The compiler sees the empty (weak) fn_actions and generates a warning
    // This function should not be called in that case, so the warning is too strict
    // If this function is called however, the keymap should have overridden fn_actions, and then the compile
    // is comparing against the wrong array
#ifdef __GNUC__
    #pragma GCC diagnostic push
    #pragma GCC diagnostic ignored "-Warray-bounds"
	return pgm_read_word(&fn_actions[function_id]);
    #pragma GCC diagnostic pop
#else
	return pgm_read_word(&fn_actions[function_id]);
#endif
}
