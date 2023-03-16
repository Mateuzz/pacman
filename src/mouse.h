#pragma once

#include <SDL.h>

#include "point.h"

#define MOUSE_WAS_PRESSED(mouse)                                               \
    ((mouse).currentEvent.type == SDL_MOUSEBUTTONDOWN)

#define MOUSE_WAS_RELEASED(mouse)                                              \
    ((mouse).currentEvent.type == SDL_MOUSEBUTTONUP)

#define MOUSE_WAS_PRESSED_LEFT(mouse)                                          \
    ((mouse).currentEvent.button == SDL_BUTTON_LEFT && MOUSE_WAS_PRESSED(mouse))

#define MOUSE_WAS_PRESSED_RIGHT(mouse)                                         \
    ((mouse).currentEvent.button == SDL_BUTTON_RIGHT &&                        \
     MOUSE_WAS_PRESSED(mouse))

#define MOUSE_WAS_PRESSED_MIDDLE(mouse)                                        \
    ((mouse).currentEvent.button == SDL_BUTTON_MIDDLE &&                       \
     MOUSE_WAS_PRESSED(mouse))

#define MOUSE_WAS_RELEASED_LEFT(mouse)                                         \
    ((mouse).currentEvent.button == SDL_BUTTON_LEFT &&                         \
     MOUSE_WAS_RELEASED(mouse))

#define MOUSE_WAS_RELEASED_RIGHT(mouse)                                        \
    ((mouse).currentEvent.button == SDL_BUTTON_RIGHT &&                        \
     MOUSE_WAS_RELEASED(mouse))

#define MOUSE_WAS_RELEASED_MIDDLE(mouse)                                       \
    ((mouse).currentEvent.button == SDL_BUTTON_MIDDLE &&                       \
     MOUSE_WAS_RELEASED(mouse))

#define MOUSE_IS_LEFT_DOWN(mouse)                                              \
    ((mouse).currentState & SDL_BUTTON(SDL_BUTTON_LEFT))

#define MOUSE_IS_RIGHT_DOWN(mouse)                                             \
    ((mouse).currentState & SDL_BUTTON(SDL_BUTTON_RIHT))

#define MOUSE_IS_MIDDLE_DOWN(mouse)                                            \
    ((mouse).currentState & SDL_BUTTON(SDL_BUTTON_MIDDLE))

typedef struct {
    Uint32 type;
    Uint8 button;
    Uint8 clicks;
} MouseEvent;

typedef struct {
    MouseEvent currentEvent; // para ser usado com os MACROS acima somente
    Uint8 currentState;
    Point moviment;
    Point position;
    Point scroll;
} Mouse;

extern void mouseReset(Mouse *mouse);
extern void mouseHandleEvent(Mouse *mouse, const SDL_Event *event);
