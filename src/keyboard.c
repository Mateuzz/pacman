#include <string.h>

#include "keyboard.h"

extern void keyReset(KeyBoard *keyBoard) {
    memset(keyBoard->events, 0, sizeof(keyBoard->events));
    keyBoard->state = SDL_GetKeyboardState(NULL);
}

extern void keyHandleEvent(KeyBoard *keyBoard, const SDL_Event *event) {
    switch (event->type) {
    case SDL_KEYDOWN:
    case SDL_KEYUP:
        if (!event->key.repeat) {
            keyBoard->events[event->key.keysym.scancode].mod =
                event->key.keysym.mod;
            keyBoard->events[event->key.keysym.scancode].type = event->type;
        }
        break;

    default:
        break;
    }
}
