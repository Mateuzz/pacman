#pragma once

#include <SDL.h>

#define NUMERO_DIRECOES 4

typedef SDL_Point Point;
typedef SDL_Rect Rect;

typedef struct {
    float x;
    float y;
} Vetor2;

typedef enum { CIMA, BAIXO, DIREITA, ESQUERDA } Direcao;

extern Vetor2 novaPosicaoPersonagem(Vetor2 posicaoAtual,
                                    float dt,
                                    Direcao direcao,
                                    Vetor2 velocidadeMax);
