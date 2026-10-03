#define _POSIX_C_SOURCE 200809L

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <assert.h>

// Public interface
typedef enum {
    // Digits
    SAD_KEY_0,
    SAD_KEY_1,
    SAD_KEY_2,
    SAD_KEY_3,
    SAD_KEY_4,
    SAD_KEY_5,
    SAD_KEY_6,
    SAD_KEY_7,
    SAD_KEY_8,
    SAD_KEY_9,

    // Letters
    SAD_KEY_A,
    SAD_KEY_B,
    SAD_KEY_C,
    SAD_KEY_D,
    SAD_KEY_E,
    SAD_KEY_F,
    SAD_KEY_G,
    SAD_KEY_H,
    SAD_KEY_I,
    SAD_KEY_J,
    SAD_KEY_K,
    SAD_KEY_L,
    SAD_KEY_M,
    SAD_KEY_N,
    SAD_KEY_O,
    SAD_KEY_P,
    SAD_KEY_Q,
    SAD_KEY_R,
    SAD_KEY_S,
    SAD_KEY_T,
    SAD_KEY_U,
    SAD_KEY_V,
    SAD_KEY_W,
    SAD_KEY_X,
    SAD_KEY_Y,
    SAD_KEY_Z,

    // Function keys
    SAD_KEY_F1,
    SAD_KEY_F2,
    SAD_KEY_F3,
    SAD_KEY_F4,
    SAD_KEY_F5,
    SAD_KEY_F6,
    SAD_KEY_F7,
    SAD_KEY_F8,
    SAD_KEY_F9,
    SAD_KEY_F10,
    SAD_KEY_F11,
    SAD_KEY_F12,

    // Mouse keys
    SAD_KEY_M1,
    SAD_KEY_M2,
    SAD_KEY_M3,
    SAD_KEY_M4,
    SAD_KEY_M5,
    SAD_KEY_M6,
    SAD_KEY_M7,
    SAD_KEY_M8,
    SAD_KEY_M9,

    // Symbol keys (US layout)
    SAD_KEY_GRAVE,         // `
    SAD_KEY_MINUS,         // -
    SAD_KEY_EQUAL,         // =
    SAD_KEY_LEFT_BRACKET,  // [
    SAD_KEY_RIGHT_BRACKET, // ]
    SAD_KEY_BACKSLASH,     // \ <-
    SAD_KEY_SEMICOLON,     // ;
    SAD_KEY_APOSTROPHE,    // '
    SAD_KEY_COMMA,         // ,
    SAD_KEY_PERIOD,        // .
    SAD_KEY_SLASH,         // /

    // Whitespace
    SAD_KEY_SPACE,
    SAD_KEY_TAB,

    // Editing
    SAD_KEY_BACKSPACE,
    SAD_KEY_ESCAPE,
    SAD_KEY_INSERT,
    SAD_KEY_DELETE,

    // Navigation
    SAD_KEY_HOME,
    SAD_KEY_END,
    SAD_KEY_PAGE_UP,
    SAD_KEY_PAGE_DOWN,
    SAD_KEY_UP,
    SAD_KEY_DOWN,
    SAD_KEY_LEFT,
    SAD_KEY_RIGHT,

    // Lock keys
    SAD_KEY_CAPS_LOCK,
    SAD_KEY_NUM_LOCK,
    SAD_KEY_SCROLL_LOCK,

    // Numpad
    SAD_KEY_KP_0,
    SAD_KEY_KP_1,
    SAD_KEY_KP_2,
    SAD_KEY_KP_3,
    SAD_KEY_KP_4,
    SAD_KEY_KP_5,
    SAD_KEY_KP_6,
    SAD_KEY_KP_7,
    SAD_KEY_KP_8,
    SAD_KEY_KP_9,
    SAD_KEY_KP_DECIMAL,
    SAD_KEY_KP_DIVIDE,
    SAD_KEY_KP_MULTIPLY,
    SAD_KEY_KP_SUBTRACT,
    SAD_KEY_KP_ADD,
    SAD_KEY_KP_ENTER,
    SAD_KEY_KP_EQUAL,

    // Misc
    SAD_KEY_ENTER,
    SAD_KEY_PRINT_SCREEN,
    SAD_KEY_PAUSE,
    SAD_KEY_MENU, /* "application" / context-menu key */

    // ---
    SAD_KEY_COUNT,
} key_e;

enum key_state_e {
    SAD_KEY_STATE_UP,
    SAD_KEY_STATE_PRESSED,
    SAD_KEY_STATE_DOWN,
    SAD_KEY_STATE_RELEASED
};

typedef struct {
    key_e key;
    bool with_ctrl  : 1;
    bool with_shift : 1;
    bool with_alt   : 1;
    bool with_win   : 1;
} hotkey_t;

extern const char * get_input_system_error();

extern hotkey_t parse_hotkey(const char * const s);
extern const char * stringify_hotkey(hotkey_t k);

/* The key the user enterred as according to their layout.
 */
extern int read_logical_key(void);

/* True if the hotkey was previously bound
 * bind() will overwrite
 */
extern bool bind(hotkey_t k, int v);
extern bool unbind(hotkey_t k);

extern const char * stringify_hotkeys_at(int v);

extern bool is_pressed(int v);
extern bool is_down(int v);
extern bool is_released(int v);

/* Calling multiple times per update breaks edge detection.
 * Zero on success.
 */
extern int read_input(void);
