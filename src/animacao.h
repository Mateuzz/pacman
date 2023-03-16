#pragma once

#include "tilemap.h"

typedef struct Animacao {
    Tilemap *tilemap;
    int *tilemapValores;
    size_t numeroAnimacoes;
    size_t tamanho;
    float fps;
    float frameAtual;
    bool infinita;
} Animacao;

extern void atualizarAnimacao(Animacao *animacao, float dt);
extern void deletarAnimacao(Animacao *animacao);

SDL_FORCE_INLINE void renderizarAnimacao(const Animacao *animacao,
                                         SDL_Renderer *render,
                                         const SDL_Rect *destino,
                                         float angulo) {
    renderizarTile(animacao->tilemap,
                   animacao->tilemapValores[(int)animacao->frameAtual],
                   render,
                   destino,
                   angulo);
}
