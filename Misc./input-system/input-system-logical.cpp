#include "input-system.hpp"
#include <stdint.h>
#include <stdarg.h>
#include <alloca.h>
#include <map>
#include <unordered_map>
#include <string>

uint64_t encode_hotkey(hotkey_t k);
hotkey_t decode_hotkey(uint64_t e);

void post_input_system_error(const char * format, ...);

static bool is_one_of(const char * token, const char * const * list, size_t n);
static bool is_mkey(const char * token);
static bool is_fkey(const char * token);
static bool is_simple_key(const char * token);
static key_e mkey_to_key_e(const char * token);
static bool key_from_simple_char(char c, key_e * out);
static key_e fkey_to_key_e(const char * token);
static key_e special_to_key_e(const char * token);
static char * trim_space(char * token);

hotkey_t parse_hotkey(const char * const s);
const char * stringify_hotkey(hotkey_t k);

bool bind(hotkey_t k, int v);
bool unbind(hotkey_t k);

const char * stringify_hotkeys_at(int v);
 
bool is_pressed(int v);
bool is_down(int v);
bool is_released(int v);

// ---

#define STATEMENT_MAX 63
#define TOKEN_MAX 15

using namespace std;

// -- Data
static
const char * const modifier_keys[] = {
    "ctrl",
    "alt",
    "win",
    "shift",
};

static
const char * const special_keys[] = {
    "tab",
    "enter",
    "caps",
};

bool prev_keys[SAD_KEY_COUNT];
bool curr_keys[SAD_KEY_COUNT];

map<int, int> known_actions;
unordered_map<int, key_state_e> action_state;

map<int, int> hotkey_table;

// -- Encoding
uint64_t encode_hotkey(hotkey_t k) {
    int e = (int)k.key;
    e |= (k.with_ctrl  ? 1 : 0) << 8;
    e |= (k.with_shift ? 1 : 0) << 9;
    e |= (k.with_alt   ? 1 : 0) << 10;
    e |= (k.with_win   ? 1 : 0) << 11;
    return e;
}
 
hotkey_t decode_hotkey(uint64_t e) {
    hotkey_t k = {};
    k.key        = (key_e)(e & 0xFF);
    k.with_ctrl  = (e >> 8)  & 1;
    k.with_shift = (e >> 9)  & 1;
    k.with_alt   = (e >> 10) & 1;
    k.with_win   = (e >> 11) & 1;
    return k;
}

// -- Error reporting
thread_local char input_system_error_buffer[128] = {};

const char * get_input_system_error() {
    return input_system_error_buffer;
}

void post_input_system_error(const char * format, ...) {
    va_list args;
    va_start(args, format);
    vsnprintf(input_system_error_buffer, sizeof(input_system_error_buffer), format, args);
    va_end(args);
}

// -- Parsing
static
char * trim_space(char * token) {
    char * start = token;
    while (*start == ' ') {
        start++;
    }

    char * end = start + strlen(start);
    while (end > start && end[-1] == ' ') {
        end--;
    }
    *end = '\0';

    return start;
}

static
bool is_one_of(const char * token, const char * const * list, size_t n) {
    for (size_t idx = 0; idx < n; idx++) {
        if (!strcmp(token, list[idx])) {
            return true;
        }
    }
    return false;
}

static
bool is_mkey(const char * token) {
    return strlen(token) == 2
        && token[0] == 'm'
        && token[1] >= '1'
        && token[1] <= '9'
    ;
}

static
bool is_fkey(const char * token) {
    size_t len = strlen(token);

    if (len < 2
    ||  len > 3
    ||  token[0] != 'f') {
        return false;
    }

    if (len == 2) {
        return token[1] >= '1'
            && token[1] <= '9'
        ;
    }

    if (token[1] != '1') {
        return false;
    }

    return token[2] >= '0'
        && token[2] <= '2'
    ;
}

static
bool is_simple_key(const char * token) {
    if (strlen(token) != 1) {
        return false;
    }

    unsigned char c = (unsigned char)token[0];

    if (!isprint(c)
    ||  isspace(c)) {
        return false;
    }

    if (isalpha(c)
    &&  isupper(c)) {
        return false;
    }

    return true;
}

static
key_e mkey_to_key_e(const char * token) {
    int n = token[1] - '0';
    return (key_e)(SAD_KEY_M1 + (n - 1));
}
 
static
key_e fkey_to_key_e(const char * token) {
    int n = atoi(token + 1);
    return (key_e)(SAD_KEY_F1 + (n - 1));
}

static
bool key_from_simple_char(char c, key_e * out) {
    if (c >= '0' && c <= '9') {
        *out = (key_e)(SAD_KEY_0 + (c - '0'));
        return true;
    }
 
    if (c >= 'a' && c <= 'z') {
        *out = (key_e)(SAD_KEY_A + (c - 'a'));
        return true;
    }
 
    switch (c) {
        case '`':  *out = SAD_KEY_GRAVE;         return true;
        case '-':  *out = SAD_KEY_MINUS;         return true;
        case '=':  *out = SAD_KEY_EQUAL;         return true;
        case '[':  *out = SAD_KEY_LEFT_BRACKET;  return true;
        case ']':  *out = SAD_KEY_RIGHT_BRACKET; return true;
        case '\\': *out = SAD_KEY_BACKSLASH;     return true;
        case ';':  *out = SAD_KEY_SEMICOLON;     return true;
        case '\'': *out = SAD_KEY_APOSTROPHE;    return true;
        case ',':  *out = SAD_KEY_COMMA;         return true;
        case '.':  *out = SAD_KEY_PERIOD;        return true;
        case '/':  *out = SAD_KEY_SLASH;         return true;
        default: return false;
    }
}

static
key_e special_to_key_e(const char * token) {
    if (!strcmp(token, "tab"))   return SAD_KEY_TAB;
    if (!strcmp(token, "enter")) return SAD_KEY_ENTER;
    if (!strcmp(token, "caps"))  return SAD_KEY_CAPS_LOCK;
    abort();
}

hotkey_t parse_hotkey(const char * const s) {
    assert(s);
 
    hotkey_t invalid = {};
    invalid.key = SAD_KEY_COUNT;
 
    if (*s == '\0') {
        post_input_system_error("hotkey: empty input");
        return invalid;
    }
 
    size_t len = strlen(s);
 
    if (len > STATEMENT_MAX) {
        post_input_system_error("hotkey: input exceeds maximum length of %d characters", STATEMENT_MAX);
        return invalid;
    }
 
    char * buf = (char*)alloca(len + 1);
    memcpy(buf, s, len + 1);
 
    char * saveptr = nullptr;
    char * token = strtok_r(buf, "+", &saveptr);
 
    if (token == nullptr) {
        post_input_system_error("hotkey: no components found");
        return invalid;
    }
 
    hotkey_t r = {};
    r.key = SAD_KEY_COUNT;
    bool have_key = false;
 
    while (token != nullptr) {
        char * key = trim_space(token);
 
        if (*key == '\0') {
            post_input_system_error("hotkey: empty component");
            return invalid;
        }
 
        if (strlen(key) > TOKEN_MAX) {
            post_input_system_error("hotkey: component '%s' exceeds maximum length of %d", key, TOKEN_MAX);
            return invalid;
        }
 
        if (is_one_of(key, modifier_keys, sizeof modifier_keys / sizeof *modifier_keys)) {
            if      (!strcmp(key, "ctrl"))  { r.with_ctrl  = true; }
            else if (!strcmp(key, "alt"))   { r.with_alt   = true; }
            else if (!strcmp(key, "win"))   { r.with_win   = true; }
            else if (!strcmp(key, "shift")) { r.with_shift = true; }
        } else if (is_one_of(key, special_keys, sizeof special_keys / sizeof *special_keys)) {
            if (have_key) {
                post_input_system_error("hotkey: more than one main key specified ('%s')", key);
                return invalid;
            }
            r.key = special_to_key_e(key);
            have_key = true;
        } else if (is_fkey(key)) {
            if (have_key) {
                post_input_system_error("hotkey: more than one main key specified ('%s')", key);
                return invalid;
            }
            r.key = fkey_to_key_e(key);
            have_key = true;
        } else if (is_mkey(key)) {
            if (have_key) {
                post_input_system_error("hotkey: more than one main key specified ('%s')", key);
                return invalid;
            }
            r.key = mkey_to_key_e(key);
            have_key = true;
        } else if (is_simple_key(key)) {
            key_e k;
            if (!key_from_simple_char(key[0], &k)) {
                post_input_system_error("hotkey: unrecognized key '%s'", key);
                return invalid;
            }
            if (have_key) {
                post_input_system_error("hotkey: more than one main key specified ('%s')", key);
                return invalid;
            }
            r.key = k;
            have_key = true;
        } else {
            post_input_system_error("hotkey: unrecognized key '%s'", key);
            return invalid;
        }
 
        token = strtok_r(nullptr, "+", &saveptr);
    }
 
    if (!have_key) {
        post_input_system_error("hotkey: no main key specified");
        return invalid;
    }
 
    return r;
}

const char * stringify_hotkey(hotkey_t k) {
    if (k.key == SAD_KEY_COUNT) {
        post_input_system_error("stringify_hotkey: invalid hotkey");
        return nullptr;
    }
 
    string key_token;
 
    if (k.key == SAD_KEY_TAB) {
        key_token = "tab";
    } else if (k.key == SAD_KEY_ENTER) {
        key_token = "enter";
    } else if (k.key == SAD_KEY_CAPS_LOCK) {
        key_token = "caps";
    } else if (k.key >= SAD_KEY_0 && k.key <= SAD_KEY_9) {
        key_token = string(1, (char)('0' + (k.key - SAD_KEY_0)));
    } else if (k.key >= SAD_KEY_A && k.key <= SAD_KEY_Z) {
        key_token = string(1, (char)('a' + (k.key - SAD_KEY_A)));
    } else if (k.key >= SAD_KEY_F1 && k.key <= SAD_KEY_F12) {
        key_token = "f" + to_string((k.key - SAD_KEY_F1) + 1);
    } else if (k.key >= SAD_KEY_M1 && k.key <= SAD_KEY_M9) {
        key_token = "m" + to_string((k.key - SAD_KEY_M1) + 1);
    } else {
        static const struct { key_e key; char ch; } symbols[] = {
            { SAD_KEY_GRAVE,         '`'  },
            { SAD_KEY_MINUS,         '-'  },
            { SAD_KEY_EQUAL,         '='  },
            { SAD_KEY_LEFT_BRACKET,  '['  },
            { SAD_KEY_RIGHT_BRACKET, ']'  },
            { SAD_KEY_BACKSLASH,     '\\' },
            { SAD_KEY_SEMICOLON,     ';'  },
            { SAD_KEY_APOSTROPHE,    '\'' },
            { SAD_KEY_COMMA,         ','  },
            { SAD_KEY_PERIOD,        '.'  },
            { SAD_KEY_SLASH,         '/'  },
        };
 
        for (auto & sym : symbols) {
            if (sym.key == k.key) {
                key_token = string(1, sym.ch);
                break;
            }
        }
    }
 
    if (key_token.empty()) {
        post_input_system_error("stringify_hotkey: key has no textual representation");
        return nullptr;
    }
 
    string result;
    if (k.with_ctrl)  result += "ctrl+";
    if (k.with_shift) result += "shift+";
    if (k.with_alt)   result += "alt+";
    if (k.with_win)   result += "win+";
    result += key_token;
 
    thread_local string buf;
    buf = move(result);
    return buf.c_str();
}

// -- Binding
bool bind(hotkey_t k, int v) {
    if (k.key == SAD_KEY_COUNT) {
        post_input_system_error("bind: refusing to bind an invalid hotkey");
        return false;
    }
 
    int encoded = encode_hotkey(k);
    bool was_bound = hotkey_table.count(encoded) != 0;
 
    hotkey_table[encoded] = v;
    known_actions[v] = encoded;
 
    if (!action_state.count(v)) {
        action_state[v] = SAD_KEY_STATE_UP;
    }
 
    return was_bound;
}
 
bool unbind(hotkey_t k) {
    int encoded = encode_hotkey(k);
    auto it = hotkey_table.find(encoded);
 
    if (it == hotkey_table.end()) {
        post_input_system_error("unbind: hotkey was not bound");
        return false;
    }
 
    int v = it->second;
    hotkey_table.erase(it);
    known_actions.erase(v);
    action_state.erase(v);
 
    return true;
}

// --
const char * stringify_hotkeys_at(int v) {
    thread_local char buf[STATEMENT_MAX * 2];
    const size_t cap = sizeof buf - 1;
 
    buf[0] = '\0';
    size_t len = 0;
 
    for (auto & [encoded, action_id] : hotkey_table) {
        if (action_id != v) {
            continue;
        }
 
        const char * s = stringify_hotkey(decode_hotkey(encoded));
 
        if (s == nullptr) {
            continue;
        }
 
        size_t s_len = strlen(s);
        size_t sep_len = (len > 0) ? 1 : 0;
 
        if (len + sep_len + s_len > cap) {
            break;
        }
 
        if (sep_len) {
            buf[len++] = ':';
        }
 
        memcpy(buf + len, s, s_len);
        len += s_len;
        buf[len] = '\0';
    }
 
    return buf;
}

// -- State reading
bool is_pressed(int v) {
    auto it = action_state.find(v);
    return it != action_state.end() && it->second == SAD_KEY_STATE_PRESSED;
}
 
bool is_down(int v) {
    auto it = action_state.find(v);
    return it != action_state.end()
        && (it->second == SAD_KEY_STATE_PRESSED || it->second == SAD_KEY_STATE_DOWN);
}
 
bool is_released(int v) {
    auto it = action_state.find(v);
    return it != action_state.end() && it->second == SAD_KEY_STATE_RELEASED;
}
