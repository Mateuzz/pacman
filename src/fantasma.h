#pragma once

#include "animacao.h"
#include "point.h"
#include "mapa.h"

typedef struct {
    Animacao animacoes[NUMERO_DIRECOES];
    Direcao direcao;
    Vetor2 quinaEsquerdaSuperior;
    Point dimensoes;
} Fantasma;

extern void atualizarFantasma(Fantasma *fantasma, float dt, const Mapa *mapa);
