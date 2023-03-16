#include "animacao.h"

#include <assert.h>

extern void atualizarAnimacao(Animacao *animacao, float dt) {
    assert(animacao != NULL);
    assert(animacao->tilemap != NULL);

    animacao->frameAtual += animacao->fps * dt;

    if (animacao->frameAtual >= animacao->numeroAnimacoes) {
        if (animacao->infinita) {
            do {
                animacao->frameAtual -= animacao->numeroAnimacoes;
            } while (animacao->frameAtual >= animacao->numeroAnimacoes);
        }
    }
}

extern void deletarAnimacao(Animacao *animacao) {
    free(animacao->tilemapValores);
    animacao->tilemapValores  = NULL;
    animacao->tilemap         = NULL;
    animacao->numeroAnimacoes = animacao->tamanho = 0;
}
