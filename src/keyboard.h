#pragma once

#include <SDL.h>

#define KEY_WAS_PRESSED(keyboard, code)                                        \
    ((keyboard).events[code].type == SDL_KEYDOWN)

#define KEY_WAS_RELEASED(keyboard, code)                                       \
    ((keyboard).events[code].type == SDL_KEYUP)

#define KEY_WAS_PRESSED_MOD(keyboard, code, mod)                               \
    (KEY_WAS_PRESSED((keyboard), code) && (keyboard).events[code].mod & mod)

#define KEY_WAS_RELEASED_MOD(keyboard, code, mod)                              \
    (KEY_WAS_RELEASED((keyboard), code) && (keyboard).events[code].mod & mod)

#define KEY_IS_DOWN(keyboard, code) ((_Bool)(keyboard).state[code])

typedef struct {
    Uint32 type;
    Uint16 mod;
} KeyEvent;

typedef struct {
    KeyEvent events[SDL_NUM_SCANCODES];
    const Uint8 *state;
} KeyBoard;

extern void keyReset(KeyBoard *keyBoard);
extern void keyHandleEvent(KeyBoard *keyBoard, const SDL_Event *event);
