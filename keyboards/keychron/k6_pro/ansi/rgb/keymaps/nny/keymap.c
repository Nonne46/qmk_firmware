#include "action_layer.h"
#include "keycodes.h"
#include "quantum.h"
#include "quantum/leader.h"
#include "quantum/digitizer.h"

#include QMK_KEYBOARD_H
#include "common.h"
#include "config.h"

void keyboard_post_init_user(void) {
    rgb_matrix_mode(RGB_MATRIX_TYPING_HEATMAP);
}

static uint16_t lead_mo_timer = 0;

bool process_mouse_jumps(uint16_t keycode, keyrecord_t *record) {
    if (record->event.pressed) {
        float x = 0.0f;
        float y = 0.0f;

        switch (keycode) {
            case KC_MOUSE_TOP_CENTER: // Top Center
                x = 0.5f;
                y = MS_J_MARGIN;
                break;
            case KC_MOUSE_TOP_LEFT: // Top Left Corner
                x = MS_J_MARGIN;
                y = MS_J_MARGIN;
                break;
            case KC_MOUSE_TOP_RIGHT: // Top Right Corner
                x = 1.0f - MS_J_MARGIN;
                y = MS_J_MARGIN;
                break;
            case KC_MOUSE_CENTER: // Center
                x = 0.5f;
                y = 0.5f;
                break;
            case KC_MOUSE_CENTER_LEFT: // Center Left
                x = MS_J_MARGIN;
                y = 0.5f;
                break;
            case KC_MOUSE_CENTER_RIGHT: // Center Right
                x = 1.0f - MS_J_MARGIN;
                y = 0.5f;
                break;
            case KC_MOUSE_BOTTOM_CENTER: // Bottom Center
                x = 0.5f;
                y = 1.0f - MS_J_MARGIN;
                break;
            case KC_MOUSE_BOTTOM_LEFT: // Bottom Left Corner
                x = MS_J_MARGIN;
                y = 1.0f - MS_J_MARGIN;
                break;
            case KC_MOUSE_BOTTOM_RIGHT: // Bottom Right Corner
                x = 1.0f - MS_J_MARGIN;
                y = 1.0f - MS_J_MARGIN;
                break;
            default:
                return true;
        }

        digitizer_in_range_on();
        digitizer_set_position(x, y);
        digitizer_in_range_off();
        digitizer_flush();
        return false;
    }

    return true;
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    if (!process_mouse_jumps(keycode, record)) return false;

    switch (keycode) {
        case KC_LOL:
            if (record->event.pressed) {
                SEND_STRING("LOL\n");
            }
            return false;
        case KC_TRIPLE_A:
            if (record->event.pressed) {
                SEND_STRING("AAA\n");
                return false;
            }
        case KC_MO_LEAD:
            if (record->event.pressed) {
                lead_mo_timer = timer_read();
                layer_on(FN2);
            } else {
                layer_off(FN2);

                if (timer_elapsed(lead_mo_timer) < TAPPING_TERM) {
                    leader_start();
                }
            }
            return false;
    }

    return true;
}

void leader_end_user(void) {
    if (leader_sequence_two_keys(KC_D, KC_D)) {
        // Leader, d, d => Discord Last Message Delete
        SEND_STRING(SS_TAP(X_ESC) SS_TAP(X_UP) SS_LCTL("a") SS_TAP(X_BSPC) SS_TAP(X_ENTER) SS_TAP(X_ENTER));
    } else if (leader_sequence_two_keys(KC_L, KC_D)) {
        // Leader, l, d => Link of deepl.com
        SEND_STRING("https://deepl.com/\n");
    } else if (leader_sequence_two_keys(KC_M, KC_M)) {
        // Leader, m, m => Mouse Mode
        layer_on(MASTERMOUSE_MODE);
    } else if (leader_sequence_one_key(KC_WH_D)) {
        // Leader, m again => Disable Mouse Mode
        layer_off(MASTERMOUSE_MODE);
    }
}

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[MAC_BASE] = LAYOUT_ansi_68(
     KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, RGB_MOD,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_HOME,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,  KC_PGUP,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,
     KC_LCTL,  KC_LOPTN, KC_LCMMD,                               KC_SPC,                       KC_RCMMD,MO(MAC_FN1),MO(FN2), KC_LEFT,  KC_DOWN, KC_RGHT),

[WIN_BASE] = LAYOUT_ansi_68(
     KC_ESC,   KC_1,     KC_2,     KC_3,     KC_4,     KC_5,     KC_6,     KC_7,     KC_8,     KC_9,     KC_0,     KC_MINS,  KC_EQL,   KC_BSPC, RGB_MOD,
     KC_TAB,   KC_Q,     KC_W,     KC_E,     KC_R,     KC_T,     KC_Y,     KC_U,     KC_I,     KC_O,     KC_P,     KC_LBRC,  KC_RBRC,  KC_BSLS, KC_HOME,
     KC_CAPS,  KC_A,     KC_S,     KC_D,     KC_F,     KC_G,     KC_H,     KC_J,     KC_K,     KC_L,     KC_SCLN,  KC_QUOT,            KC_ENT,  KC_PGUP,
     KC_LSFT,  KC_Z,     KC_X,     KC_C,     KC_V,     KC_B,     KC_N,     KC_M,     KC_COMM,  KC_DOT,   KC_SLSH,  KC_RSFT,  KC_UP,    KC_PGDN,
     KC_LCTL,  KC_LGUI,  MO(MOUSE_MODE),                                KC_SPC,                       KC_RALT, MO(WIN_FN1), KC_MO_LEAD, KC_LEFT,  KC_DOWN, KC_RGHT),

[MAC_FN1] = LAYOUT_ansi_68(
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_MCTL,  KC_LPAD,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[WIN_FN1] = LAYOUT_ansi_68(
     KC_GRV,   KC_BRID,  KC_BRIU,  KC_TASK,  KC_FILE,  RGB_VAD,  RGB_VAI,  KC_MPRV,  KC_MPLY,  KC_MNXT,  KC_MUTE,  KC_VOLD,  KC_VOLU,  KC_TRNS,  RGB_TOG,
     KC_TRNS,  BT_HST1,  BT_HST2,  BT_HST3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     RGB_TOG,  RGB_MOD,  RGB_VAI,  RGB_HUI,  RGB_SAI,  RGB_SPI,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,
     KC_TRNS,  RGB_RMOD, RGB_VAD,  RGB_HUD,  RGB_SAD,  RGB_SPD,  NK_TOGG,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[FN2] = LAYOUT_ansi_68(
     KC_TILD,  KC_F1,    KC_F2,    KC_F3,    KC_F4,    KC_F5,    KC_F6,    KC_F7,    KC_F8,    KC_F9,    KC_F10,   KC_F11,   KC_F12,   KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_U,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_LOL,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_BTN3,  KC_BTN2,  KC_BTN1,  BAT_LVL,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),


[MOUSE_MODE] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_MOUSE_TOP_LEFT,  KC_MOUSE_TOP_CENTER,  KC_MOUSE_TOP_RIGHT,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_MOUSE_CENTER_LEFT,  KC_MOUSE_CENTER,  KC_MOUSE_CENTER_RIGHT,  KC_TRNS,  KC_TRNS,  KC_WH_D,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_WH_U,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_MOUSE_BOTTOM_LEFT,  KC_MOUSE_BOTTOM_CENTER,  KC_MOUSE_BOTTOM_RIGHT,  KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_BTN2,  KC_BTN3,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),

[MASTERMOUSE_MODE] = LAYOUT_ansi_68(
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_MS_U,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_WH_L,  KC_WH_R,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_MS_L,  KC_MS_D,  KC_MS_R,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_BTN1,  KC_BTN2,  KC_BTN3,  KC_TRNS,            KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_WH_D,  KC_WH_U,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
     KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),
};

// [DUMMY] = LAYOUT_ansi_68(
//      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
//      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
//      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,            KC_TRNS,  KC_TRNS,
//      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,
//      KC_TRNS,  KC_TRNS,  KC_TRNS,                                KC_TRNS,                      KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS,  KC_TRNS),