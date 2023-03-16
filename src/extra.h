#pragma once

#include <SDL.h>

#include "bool.h"
#include "point.h"

#define UNUSED_PARAMETER(p) ((void)p)
#define HAS_FLAG(p, flag)   ((p) & (flag))

#define VALOR_XY(i, j, xMax) ((i) * (xMax) + (j))

#define SIZE_ARRAY(a) (sizeof a / sizeof a[0])

extern char csvErro[200];

extern int *carregarCSV(const char *arquivo, char separador, Point *qtd);

SDL_FORCE_INLINE float grausParaRadianos(float g) {
    return g / 180.0f * M_PI;
}

SDL_FORCE_INLINE bool retColide(const Rect *r1, const Rect *r2) {
    return !(r1->x + r1->w < r2->x || r1->y + r1->h < r2->y ||
             r2->x + r2->w < r1->x || r2->y + r2->h < r2->y);
}

SDL_FORCE_INLINE float parteFracao(float f) {
    return f - (int)f;
}
