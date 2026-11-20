/*
 * OLED for the right half (the only one with a screen): bongo cat on the
 * left 96 columns, a 5-character status column on the right 32.
 *
 * The right half is the slave, so the state it shows (layer, mods,
 * one-shot AltGr, Caps Lock, WPM) is synced from the left half; see the
 * SPLIT_*_ENABLE settings in config.h.
 */

#include QMK_KEYBOARD_H
#include "bongocat_frames.h"

// Below IDLE_WPM the cat idles; from TAP_WPM up it taps.
#define IDLE_WPM 10
#define TAP_WPM 20
#define IDLE_FRAME_MS 300
// Tap frames speed up with WPM, from TAP_FRAME_MAX_MS down to TAP_FRAME_MIN_MS.
#define TAP_FRAME_MAX_MS 450
#define TAP_FRAME_MIN_MS 100

// Status column: 5 characters starting at character column 16 (pixel 96).
#define STATUS_COL 16

static void render_bongo_frame(const char *frame) {
    for (uint8_t page = 0; page < BONGO_PAGES; page++) {
        oled_set_cursor(0, page);
        oled_write_raw_P(frame + page * BONGO_WIDTH, BONGO_WIDTH);
    }
}

static void render_bongocat(void) {
    static uint32_t    frame_timer = 0;
    static uint8_t     idle_index  = 0;
    static uint8_t     tap_index   = 0;
    static const char *frame       = NULL;

    uint8_t  wpm      = get_current_wpm();
    uint16_t duration = IDLE_FRAME_MS;

    if (wpm >= TAP_WPM) {
        int16_t tap_ms = TAP_FRAME_MAX_MS - (wpm * 5) / 2;
        duration       = tap_ms < TAP_FRAME_MIN_MS ? TAP_FRAME_MIN_MS : tap_ms;
    }

    if (frame == NULL || timer_elapsed32(frame_timer) > duration) {
        frame_timer = timer_read32();

        if (wpm >= TAP_WPM) {
            tap_index = (tap_index + 1) % 2;
            frame     = bongo_tap[tap_index];
        } else if (wpm > IDLE_WPM) {
            frame = bongo_prep[0];
        } else {
            idle_index = (idle_index + 1) % 5;
            frame      = bongo_idle[idle_index];
        }
    }

    render_bongo_frame(frame);
}

static void render_status(void) {
    // Line 0: layer.
    oled_set_cursor(STATUS_COL, 0);
    switch (get_highest_layer(layer_state)) {
        case 1:
            oled_write_P(PSTR("LOWER"), false);
            break;
        case 2:
            oled_write_P(PSTR("RAISE"), false);
            break;
        case 3:
            oled_write_P(PSTR("ADJST"), false);
            break;
        default:
            oled_write_P(PSTR("BASE "), false);
            break;
    }

    // Line 1: held or one-shot modifiers (Ctrl, Shift, Alt, GUI).
    uint8_t mods = get_mods() | get_oneshot_mods();

    oled_set_cursor(STATUS_COL, 1);
    oled_write_P((mods & MOD_MASK_CTRL) ? PSTR("C") : PSTR(" "), false);
    oled_write_P((mods & MOD_MASK_SHIFT) ? PSTR("S") : PSTR(" "), false);
    oled_write_P((mods & MOD_BIT(KC_LALT)) ? PSTR("A") : PSTR(" "), false);
    oled_write_P((mods & MOD_MASK_GUI) ? PSTR("G") : PSTR(" "), false);
    oled_write_P(PSTR(" "), false);

    // Line 2: AltGr, inverted while armed by a Raise tap (one-shot).
    oled_set_cursor(STATUS_COL, 2);
    if (get_oneshot_mods() & MOD_BIT(KC_RALT)) {
        oled_write_P(PSTR("AltGr"), true);
    } else if (get_mods() & MOD_BIT(KC_RALT)) {
        oled_write_P(PSTR("AltGr"), false);
    } else {
        oled_write_P(PSTR("     "), false);
    }

    // Line 3: Caps Lock, otherwise words per minute.
    oled_set_cursor(STATUS_COL, 3);
    if (host_keyboard_led_state().caps_lock) {
        oled_write_P(PSTR("CAPS "), true);
    } else {
        oled_write(get_u8_str(get_current_wpm(), ' '), false);
        oled_write_P(PSTR("wp"), false);
    }
}

bool oled_task_user(void) {
    // Returning false skips the Corne's default OLED rendering.
    if (is_keyboard_master()) {
        return false;
    }

    // Every redraw wakes the display and restarts the driver's timeout, and
    // the idle animation redraws every few hundred ms, so the driver alone
    // would never sleep. Sleep after OLED_TIMEOUT without input instead, and
    // stop drawing so nothing wakes it; the first keypress redraws it.
    if (last_input_activity_elapsed() > OLED_TIMEOUT) {
        oled_off();
        return false;
    }

    render_bongocat();
    render_status();
    return false;
}
