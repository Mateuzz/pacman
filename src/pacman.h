#pragma once

#include "animacao.h"
#include "input.h"
#include "mapa.h"
#include "point.h"
#include "tilemap.h"

#define TILE_COLIDIVEIS_PACMAN (TIPO_QUINA | TIPO_QUINA_PORTA_FANTASMA)

typedef struct {
    // Em relação ao tile do mapa - Ex: 5.5f equivale ao tile 5 e um meio a
    // frente
    Vetor2 quinaEsquerdaSuperior;
    Point dimensoes;
    Direcao direcao;
    Direcao direcaoFutura;
    Animacao animacao;
    size_t vidas;
    int pontosColetados;
    bool foiMovidoUltimaVez;
} Pacman;

extern void inputPacman(Pacman *pacman, const Input *input);
extern void atualizarPacman(Pacman *pacman, float dt, const Mapa *mapa);
extern void renderizarPacman(const Pacman *pacman, const Mapa *mapa, SDL_Renderer *render);
