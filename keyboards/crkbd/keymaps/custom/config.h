/*
This is the c configuration file for the keymap

Copyright 2012 Jun Wako <wakojun@gmail.com>
Copyright 2015 Jack Humbert

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

#pragma once

//#define USE_MATRIX_I2C

//#define QUICK_TAP_TERM 0
//#define TAPPING_TERM 100

// Default for tap-hold keys: a key pressed and released while one is held
// counts as a hold even within the tapping term. Ctrl/Esc and Raise go
// further, see get_hold_on_other_key_press() in keymap.c.
#define PERMISSIVE_HOLD

// Per-key tap/hold tuning, see get_hold_on_other_key_press() and
// get_quick_tap_term() in keymap.c.
#define HOLD_ON_OTHER_KEY_PRESS_PER_KEY
#define QUICK_TAP_TERM_PER_KEY

// An AltGr armed by tapping Raise expires after 1 s if no key follows.
#define ONESHOT_TIMEOUT 1000

#ifdef RGBLIGHT_ENABLE
    #define RGBLIGHT_EFFECT_BREATHING
    #define RGBLIGHT_EFFECT_RAINBOW_MOOD
    #define RGBLIGHT_EFFECT_RAINBOW_SWIRL
    #define RGBLIGHT_EFFECT_SNAKE
    #define RGBLIGHT_EFFECT_KNIGHT
    #define RGBLIGHT_EFFECT_CHRISTMAS
    #define RGBLIGHT_EFFECT_STATIC_GRADIENT
    #define RGBLIGHT_EFFECT_RGB_TEST
    #define RGBLIGHT_EFFECT_ALTERNATING
    #define RGBLIGHT_EFFECT_TWINKLE
    #define RGBLIGHT_LIMIT_VAL 120
    #define RGBLIGHT_HUE_STEP 10
    #define RGBLIGHT_SAT_STEP 17
    #define RGBLIGHT_VAL_STEP 17
#endif

// Decide master by actual USB enumeration, not VBUS voltage: some USB-C
// Pro Micro clones back-feed VCC from the TRRS link into VBUS, making the
// slave half wrongly think it is the master.
#define SPLIT_USB_DETECT

// The only OLED is on the right (slave) half: sync what it displays from
// the left half, and its activity so the screen times out correctly.
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_MODS_ENABLE
#define SPLIT_LED_STATE_ENABLE
#define SPLIT_WPM_ENABLE
#define SPLIT_ACTIVITY_ENABLE

// Custom message carrying the OLED on/off toggle to the right half, see
// oled.c.
#define SPLIT_TRANSACTION_IDS_USER USER_SYNC_OLED

// OLED: dimmer than the default 255, and off after 30 s without typing
// (default 60 s).
#define OLED_BRIGHTNESS 100
#define OLED_TIMEOUT 30000
