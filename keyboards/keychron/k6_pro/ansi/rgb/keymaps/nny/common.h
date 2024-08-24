#include QMK_KEYBOARD_H

enum layers {
    MAC_BASE,
    WIN_BASE,
    MAC_FN1,
    WIN_FN1,
    FN2,
    MASTERMOUSE_MODE,
    MOUSE_MODE,
};

enum mein_keys {
    // Fun keys
    KC_LOL = SAFE_RANGE,
    KC_TRIPLE_A,

    // Leader key
    KC_MO_LEAD,

    // Jumps Keys
    KC_MOUSE_TOP_CENTER,
    KC_MOUSE_TOP_LEFT,
    KC_MOUSE_TOP_RIGHT,
    KC_MOUSE_CENTER,
    KC_MOUSE_CENTER_LEFT,
    KC_MOUSE_CENTER_RIGHT,
    KC_MOUSE_BOTTOM_CENTER,
    KC_MOUSE_BOTTOM_LEFT,
    KC_MOUSE_BOTTOM_RIGHT,
};