#pragma once

#include "keyboard.h"
#include "mouse.h"

typedef struct {
    Mouse mouse;
    KeyBoard key;
} Input;

SDL_FORCE_INLINE void inputReset(Input *input) {
    keyReset(&input->key);
    mouseReset(&input->mouse);
}

SDL_FORCE_INLINE void inputHandleEvent(Input *input, const SDL_Event *event) {
    keyHandleEvent(&input->key, event);
    mouseHandleEvent(&input->mouse, event);
}
