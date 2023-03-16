#include "pacman.h"
#include "extra.h"
#include "point.h"

#include <math.h>

static int anguloPacman(int direcao) {
    static const int angulosPacman[] = {90, -90, 0, 180};
    return angulosPacman[direcao];
}

extern void inputPacman(Pacman *pacman, const Input *input) {
    if (KEY_WAS_PRESSED(input->key, SDL_SCANCODE_RIGHT)) {
        pacman->direcaoFutura = DIREITA;
    }
    if (KEY_WAS_PRESSED(input->key, SDL_SCANCODE_LEFT)) {
        pacman->direcaoFutura = ESQUERDA;
    }
    if (KEY_WAS_PRESSED(input->key, SDL_SCANCODE_UP)) {
        pacman->direcaoFutura = CIMA;
    }
    if (KEY_WAS_PRESSED(input->key, SDL_SCANCODE_DOWN)) {
        pacman->direcaoFutura = BAIXO;
    }
}

extern void atualizarPacman(Pacman *pacman, float dt, const Mapa *mapa) {
    atualizarAnimacao(&pacman->animacao, dt);

    Vetor2 posicaoEsperadaSeMudarDirecao =
        novaPosicaoPersonagem(pacman->quinaEsquerdaSuperior,
                              dt,
                              pacman->direcaoFutura,
                              (Vetor2){4.5f, 4.5f});

    if (!pacman->foiMovidoUltimaVez || !colideMapa(mapa,
                                           posicaoEsperadaSeMudarDirecao,
                                           TILE_COLIDIVEIS_PACMAN)) {
        pacman->direcao = pacman->direcaoFutura;
    }

    pacman->foiMovidoUltimaVez = moverPersonagem(mapa,
                                         &pacman->quinaEsquerdaSuperior,
                                         (Vetor2){4.5f, 4.5f},
                                         pacman->direcao,
                                         TILE_COLIDIVEIS_PACMAN,
                                         dt);

    if (pacman->quinaEsquerdaSuperior.x < 0) {
        pacman->quinaEsquerdaSuperior.x = mapa->grafo.qtdTiles.x - 1;
    } else if (pacman->quinaEsquerdaSuperior.x + 1 >= mapa->grafo.qtdTiles.x) {
        pacman->quinaEsquerdaSuperior.x = 0;
    } else {
        Point pontoCentro = tileDoCentro(pacman->quinaEsquerdaSuperior);

        NoGrafoMapa *noDoCentro =
            &GRAFO_NO(mapa->grafo, pontoCentro.y, pontoCentro.x);

        if (HAS_FLAG(noDoCentro->tipo.items,
                     MAPA_ITEM_PONTO | MAPA_ITEM_PONTO_ENERGIZANTE)) {
            noDoCentro->tipo.items = 0;
            pacman->pontosColetados += 15;
        }
    }
}

extern void
renderizarPacman(const Pacman *pacman, const Mapa *mapa, SDL_Renderer *render) {
    renderizarAnimacaoNoMapa(mapa,
                             render,
                             &pacman->animacao,
                             pacman->quinaEsquerdaSuperior,
                             pacman->dimensoes,
                             anguloPacman(pacman->direcao));
}
