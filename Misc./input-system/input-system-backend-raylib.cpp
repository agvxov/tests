#include "input-system.hpp"
#include <raylib.h>
#include <stdint.h>
#include <map>
#include <unordered_map>
/* The radio active core of the input system, provided by raylib.
 */
// Extern
using namespace std;

extern uint64_t encode_hotkey(hotkey_t k);
extern hotkey_t decode_hotkey(uint64_t e);

extern bool prev_keys[SAD_KEY_COUNT];
extern bool curr_keys[SAD_KEY_COUNT];

extern map<int, int> hotkey_table;
extern unordered_map<int, key_state_e> action_state;

// Intern
static bool sad_key_is_down(key_e k);
static int key_state_rank(key_state_e s);
int read_input(void);
int read_logical_key(void);

// ---

static
bool sad_key_is_down(key_e k) {
    if (k >= SAD_KEY_M1 && k <= SAD_KEY_M9) {
        return IsMouseButtonDown(k - SAD_KEY_M1);
    }
 
    int rk = -1;
 
    switch (k) {
        case SAD_KEY_0: rk = KEY_ZERO;  break;
        case SAD_KEY_1: rk = KEY_ONE;   break;
        case SAD_KEY_2: rk = KEY_TWO;   break;
        case SAD_KEY_3: rk = KEY_THREE; break;
        case SAD_KEY_4: rk = KEY_FOUR;  break;
        case SAD_KEY_5: rk = KEY_FIVE;  break;
        case SAD_KEY_6: rk = KEY_SIX;   break;
        case SAD_KEY_7: rk = KEY_SEVEN; break;
        case SAD_KEY_8: rk = KEY_EIGHT; break;
        case SAD_KEY_9: rk = KEY_NINE;  break;
 
        case SAD_KEY_A: rk = KEY_A; break;
        case SAD_KEY_B: rk = KEY_B; break;
        case SAD_KEY_C: rk = KEY_C; break;
        case SAD_KEY_D: rk = KEY_D; break;
        case SAD_KEY_E: rk = KEY_E; break;
        case SAD_KEY_F: rk = KEY_F; break;
        case SAD_KEY_G: rk = KEY_G; break;
        case SAD_KEY_H: rk = KEY_H; break;
        case SAD_KEY_I: rk = KEY_I; break;
        case SAD_KEY_J: rk = KEY_J; break;
        case SAD_KEY_K: rk = KEY_K; break;
        case SAD_KEY_L: rk = KEY_L; break;
        case SAD_KEY_M: rk = KEY_M; break;
        case SAD_KEY_N: rk = KEY_N; break;
        case SAD_KEY_O: rk = KEY_O; break;
        case SAD_KEY_P: rk = KEY_P; break;
        case SAD_KEY_Q: rk = KEY_Q; break;
        case SAD_KEY_R: rk = KEY_R; break;
        case SAD_KEY_S: rk = KEY_S; break;
        case SAD_KEY_T: rk = KEY_T; break;
        case SAD_KEY_U: rk = KEY_U; break;
        case SAD_KEY_V: rk = KEY_V; break;
        case SAD_KEY_W: rk = KEY_W; break;
        case SAD_KEY_X: rk = KEY_X; break;
        case SAD_KEY_Y: rk = KEY_Y; break;
        case SAD_KEY_Z: rk = KEY_Z; break;
 
        case SAD_KEY_F1:  rk = KEY_F1;  break;
        case SAD_KEY_F2:  rk = KEY_F2;  break;
        case SAD_KEY_F3:  rk = KEY_F3;  break;
        case SAD_KEY_F4:  rk = KEY_F4;  break;
        case SAD_KEY_F5:  rk = KEY_F5;  break;
        case SAD_KEY_F6:  rk = KEY_F6;  break;
        case SAD_KEY_F7:  rk = KEY_F7;  break;
        case SAD_KEY_F8:  rk = KEY_F8;  break;
        case SAD_KEY_F9:  rk = KEY_F9;  break;
        case SAD_KEY_F10: rk = KEY_F10; break;
        case SAD_KEY_F11: rk = KEY_F11; break;
        case SAD_KEY_F12: rk = KEY_F12; break;
 
        case SAD_KEY_GRAVE:         rk = KEY_GRAVE;         break;
        case SAD_KEY_MINUS:         rk = KEY_MINUS;         break;
        case SAD_KEY_EQUAL:         rk = KEY_EQUAL;         break;
        case SAD_KEY_LEFT_BRACKET:  rk = KEY_LEFT_BRACKET;  break;
        case SAD_KEY_RIGHT_BRACKET: rk = KEY_RIGHT_BRACKET; break;
        case SAD_KEY_BACKSLASH:     rk = KEY_BACKSLASH;     break;
        case SAD_KEY_SEMICOLON:     rk = KEY_SEMICOLON;     break;
        case SAD_KEY_APOSTROPHE:    rk = KEY_APOSTROPHE;    break;
        case SAD_KEY_COMMA:         rk = KEY_COMMA;         break;
        case SAD_KEY_PERIOD:        rk = KEY_PERIOD;        break;
        case SAD_KEY_SLASH:         rk = KEY_SLASH;         break;
 
        case SAD_KEY_SPACE: rk = KEY_SPACE; break;
        case SAD_KEY_TAB:   rk = KEY_TAB;   break;
 
        case SAD_KEY_BACKSPACE: rk = KEY_BACKSPACE; break;
        case SAD_KEY_ESCAPE:    rk = KEY_ESCAPE;    break;
        case SAD_KEY_INSERT:    rk = KEY_INSERT;    break;
        case SAD_KEY_DELETE:    rk = KEY_DELETE;    break;
 
        case SAD_KEY_HOME:      rk = KEY_HOME;      break;
        case SAD_KEY_END:       rk = KEY_END;       break;
        case SAD_KEY_PAGE_UP:   rk = KEY_PAGE_UP;   break;
        case SAD_KEY_PAGE_DOWN: rk = KEY_PAGE_DOWN; break;
        case SAD_KEY_UP:        rk = KEY_UP;        break;
        case SAD_KEY_DOWN:      rk = KEY_DOWN;      break;
        case SAD_KEY_LEFT:      rk = KEY_LEFT;      break;
        case SAD_KEY_RIGHT:     rk = KEY_RIGHT;     break;
 
        case SAD_KEY_CAPS_LOCK:   rk = KEY_CAPS_LOCK;   break;
        case SAD_KEY_NUM_LOCK:    rk = KEY_NUM_LOCK;    break;
        case SAD_KEY_SCROLL_LOCK: rk = KEY_SCROLL_LOCK; break;
 
        case SAD_KEY_KP_0: rk = KEY_KP_0; break;
        case SAD_KEY_KP_1: rk = KEY_KP_1; break;
        case SAD_KEY_KP_2: rk = KEY_KP_2; break;
        case SAD_KEY_KP_3: rk = KEY_KP_3; break;
        case SAD_KEY_KP_4: rk = KEY_KP_4; break;
        case SAD_KEY_KP_5: rk = KEY_KP_5; break;
        case SAD_KEY_KP_6: rk = KEY_KP_6; break;
        case SAD_KEY_KP_7: rk = KEY_KP_7; break;
        case SAD_KEY_KP_8: rk = KEY_KP_8; break;
        case SAD_KEY_KP_9: rk = KEY_KP_9; break;
        case SAD_KEY_KP_DECIMAL:  rk = KEY_KP_DECIMAL;  break;
        case SAD_KEY_KP_DIVIDE:   rk = KEY_KP_DIVIDE;   break;
        case SAD_KEY_KP_MULTIPLY: rk = KEY_KP_MULTIPLY; break;
        case SAD_KEY_KP_SUBTRACT: rk = KEY_KP_SUBTRACT; break;
        case SAD_KEY_KP_ADD:      rk = KEY_KP_ADD;      break;
        case SAD_KEY_KP_ENTER:    rk = KEY_KP_ENTER;    break;
        case SAD_KEY_KP_EQUAL:    rk = KEY_KP_EQUAL;    break;
 
        case SAD_KEY_ENTER:        rk = KEY_ENTER;        break;
        case SAD_KEY_PRINT_SCREEN: rk = KEY_PRINT_SCREEN; break;
        case SAD_KEY_PAUSE:        rk = KEY_PAUSE;        break;
        case SAD_KEY_MENU:         rk = KEY_KB_MENU;      break;
 
        default: rk = -1; break; // SAD_KEY_COUNT and anything unmapped
    }
 
    if (rk < 0) {
        return false;
    }
 
    return IsKeyDown(rk);
}


static
int key_state_rank(key_state_e s) {
    switch (s) {
        case SAD_KEY_STATE_PRESSED:  return 3;
        case SAD_KEY_STATE_DOWN:     return 2;
        case SAD_KEY_STATE_RELEASED: return 1;
        case SAD_KEY_STATE_UP:       return 0;
    }
    return 0;
}

int read_input(void) {
    memcpy(prev_keys, curr_keys, sizeof curr_keys);
 
    for (int k = 0; k < SAD_KEY_COUNT; k++) {
        curr_keys[k] = sad_key_is_down((key_e)k);
    }

    bool mod_ctrl  = IsKeyDown(KEY_LEFT_CONTROL) || IsKeyDown(KEY_RIGHT_CONTROL);
    bool mod_shift = IsKeyDown(KEY_LEFT_SHIFT)   || IsKeyDown(KEY_RIGHT_SHIFT);
    bool mod_alt   = IsKeyDown(KEY_LEFT_ALT)     || IsKeyDown(KEY_RIGHT_ALT);
    bool mod_win   = IsKeyDown(KEY_LEFT_SUPER)   || IsKeyDown(KEY_RIGHT_SUPER);
 
    unordered_map<int, key_state_e> frame_state;
 
    for (auto & [encoded, action_id] : hotkey_table) {
        hotkey_t hk = decode_hotkey(encoded);
 
        bool mods_held = (hk.with_ctrl  == mod_ctrl)
                      && (hk.with_shift == mod_shift)
                      && (hk.with_alt   == mod_alt)
                      && (hk.with_win   == mod_win)
        ;
 
        bool now_down  = curr_keys[hk.key] && mods_held;
        bool prev_down = prev_keys[hk.key] && mods_held;
 
        key_state_e state;
 
        if      (now_down  && !prev_down) state = SAD_KEY_STATE_PRESSED;
        else if (now_down  &&  prev_down) state = SAD_KEY_STATE_DOWN;
        else if (!now_down &&  prev_down) state = SAD_KEY_STATE_RELEASED;
        else                               state = SAD_KEY_STATE_UP;
 
        auto it = frame_state.find(action_id);
        if (it == frame_state.end() || key_state_rank(state) > key_state_rank(it->second)) {
            frame_state[action_id] = state;
        }
    }
 
    for (auto & [action_id, state] : frame_state) {
        action_state[action_id] = state;
    }
 
    return 0;
}

int read_logical_key(void) {
    return GetCharPressed();
}
