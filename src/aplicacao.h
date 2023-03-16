#pragma once

#include "bool.h"
#include "input.h"
#include "tilemap.h"
#include "pacman.h"
#include "mapa.h"

#include <SDL.h>
#include <stdint.h>

// O estado atual do jogo, se é menu ou gameplay...
typedef enum {
    ESTADO_MENU,
    ESTADO_JOGANDO,
} EstadoJogo;

// A representação da Aplicação SDL e do jogo
typedef struct {
    Input input;
    SDL_Window *janela;
    SDL_Renderer *render;
    uint32_t tempoPassado;
    int fps;
    EstadoJogo estado;
    Tilemap pacmanPng;
    Pacman pacman;
    Mapa mapa;
} Aplicacao;

// Cria janela e inicializa o jogo
extern bool iniciarAplicacao(Aplicacao *app,
                             const char *titulo,
                             int largura,
                             int altura,
                             int flags);

// Roda a aplicação já inicializada
extern void rodarAplicacao(Aplicacao *app);

// Libera memória e desliga os sistemas do SDL
extern void deletarAplicacao(Aplicacao *app);
