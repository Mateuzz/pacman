#include "mouse.h"

extern void mouseReset(Mouse *mouse) {
    mouse->currentEvent = (MouseEvent){0};

    mouse->currentState =
        SDL_GetMouseState(&mouse->position.x, &mouse->position.y);
    SDL_GetRelativeMouseState(&mouse->moviment.x, &mouse->moviment.y);
}

extern void mouseHandleEvent(Mouse *mouse, const SDL_Event *event) {
    switch (event->type) {
    case SDL_MOUSEBUTTONDOWN:
    case SDL_MOUSEBUTTONUP:
        mouse->currentEvent.type   = event->type;
        mouse->currentEvent.button = event->button.button;
        mouse->currentEvent.clicks = event->button.clicks;
        break;

    case SDL_MOUSEWHEEL:
        mouse->scroll.x = event->wheel.x;
        mouse->scroll.y = event->wheel.y;
        break;

    default:
        break;
    }
}
