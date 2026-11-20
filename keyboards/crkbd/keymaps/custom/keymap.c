/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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

/*
 * The OS keyboard layout is Italian: every key uses the IT_* aliases from
 * keymap_italian.h, which name each keycode after the character it types
 * under the Italian layout.
 */

#include QMK_KEYBOARD_H
#include "keymap_italian.h"

// Not printed on Italian keycaps; Linux xkb "it" puts them on AltGr.
#ifndef IT_GRV
#    define IT_GRV ALGR(IT_QUOT) // `
#endif
#ifndef IT_TILD
#    define IT_TILD ALGR(IT_IGRV) // ~
#endif

// Tap = Esc, hold = Ctrl.
#define CTL_ESC LCTL_T(KC_ESC)

enum layers {
    _BASE,
    _LOWER,
    _RAISE,
    _ADJUST,
};

#define LOWER MO(_LOWER)
// Hold = Raise layer, tap = arm AltGr for the next key (one-shot), so the
// AltGr characters stay where the Italian layout has them while the left
// thumb is a real Alt. The tap is intercepted in process_record_user().
#define RAISE LT(_RAISE, KC_NO)
#define ADJUST MO(_ADJUST)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * Base: QWERTY with Italian letters, B on the right half.
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | Tab  |  Q   |  W   |  E   |  R   |  T   |                    |  Y   |  U   |  I   |  O   |  P   | Bksp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |Ctl/Es|  A   |  S   |  D   |  F   |  G   |                    |  H   |  J   |  K   |  L   |  ò   |  à   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Shft |  <   |  Z   |  X   |  C   |  V   |                    |  B   |  N   |  M   |  ,   |  .   |  -   |
     * `------+------+------+------+------+------+------.      ,------+------+------+------+------+------+------'
     *                             | Alt  | GUI  | Spc  |      | Ent  |Lower |Raise |
     *                                                                        tap: AltGr
     *                                                                   for the next key
     *                             `--------------------'      `--------------------'
     */
    [_BASE] = LAYOUT_split_3x6_3(
        KC_TAB,  IT_Q,    IT_W,    IT_E,    IT_R,    IT_T,          IT_Y,    IT_U,    IT_I,    IT_O,    IT_P,    KC_BSPC,
        CTL_ESC, IT_A,    IT_S,    IT_D,    IT_F,    IT_G,          IT_H,    IT_J,    IT_K,    IT_L,    IT_OGRV, IT_AGRV,
        KC_LSFT, IT_LABK, IT_Z,    IT_X,    IT_C,    IT_V,          IT_B,    IT_N,    IT_M,    IT_COMM, IT_DOT,  IT_MINS,
                                   KC_LALT, KC_LGUI, KC_SPC,        KC_ENT,  LOWER,   RAISE
    ),

    /*
     * Lower: numbers, function keys and navigation.
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  \   |  1   |  2   |  3   |  4   |  5   |                    |  6   |  7   |  8   |  9   |  0   |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | PgUp |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      | Home | End  | Ins  | Del  | F11  |                    | F12  | Left | Down |  Up  |Right | PgDn |
     * `------+------+------+------+------+------+------.      ,------+------+------+------+------+------+------'
     *                             |      |      |      |      |      |(held)|Adjust|
     *                             `--------------------'      `--------------------'
     */
    [_LOWER] = LAYOUT_split_3x6_3(
        IT_BSLS, IT_1,    IT_2,    IT_3,    IT_4,    IT_5,          IT_6,    IT_7,    IT_8,    IT_9,    IT_0,    _______,
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,         KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_PGUP,
        _______, KC_HOME, KC_END,  KC_INS,  KC_DEL,  KC_F11,        KC_F12,  KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_PGDN,
                                   _______, _______, _______,       _______, _______, ADJUST
    ),

    /*
     * Raise: symbols (work in progress).
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |  '   |  ì   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |      |      |  è   |  +   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |                    |      |      |      |      |      |  ù   |
     * `------+------+------+------+------+------+------.      ,------+------+------+------+------+------+------'
     *                             |      |      |      |      |      |Adjust|(held)|
     *                             `--------------------'      `--------------------'
     */
    [_RAISE] = LAYOUT_split_3x6_3(
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_QUOT, IT_IGRV,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_EGRV, IT_PLUS,
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, IT_UGRV,
                                   _______, _______, _______,       _______, ADJUST,  _______
    ),

    /*
     * Adjust (Lower + Raise): firmware, RGB and media.
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | Boot |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |RGBtog| Hue+ | Sat+ | Bri+ |      |      |                    | Prev | Vol- | Vol+ | Next | Mute |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |RGBnxt| Hue- | Sat- | Bri- |      |      |                    |      |      | Play |      |      |      |
     * `------+------+------+------+------+------+------.      ,------+------+------+------+------+------+------'
     *                             |      |      |      |      |      |(held)|(held)|
     *                             `--------------------'      `--------------------'
     */
    [_ADJUST] = LAYOUT_split_3x6_3(
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,       KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_MUTE, XXXXXXX,
        RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,       XXXXXXX, XXXXXXX, KC_MPLY, XXXXXXX, XXXXXXX, XXXXXXX,
                                   _______, _______, _______,       _______, _______, _______
    ),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RAISE:
            if (record->tap.count && record->event.pressed) {
                // Tapping Raise again cancels an armed AltGr.
                if (get_oneshot_mods() & MOD_BIT(KC_RALT)) {
                    clear_oneshot_mods();
                } else {
                    set_oneshot_mods(MOD_BIT(KC_RALT));
                }
                return false;
            }
            break;
    }
    return true;
}

// These count as held as soon as another key goes down, however fast the
// roll: Ctrl/Esc + Space is always Ctrl+Space, never Esc then Space, and a
// fast Raise + è roll never becomes a tap that arms AltGr.
bool get_hold_on_other_key_press(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case CTL_ESC:
        case RAISE:
            return true;
        default:
            return false;
    }
}

// Tap Raise, then hold it straight away: that must be a layer hold, not a
// repeated tap (which would cancel the AltGr just armed).
uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t *record) {
    if (keycode == RAISE) {
        return 0;
    }
    return QUICK_TAP_TERM;
}
