#include "point.h"
#include "extra.h"

extern Vetor2 novaPosicaoPersonagem(Vetor2 posicaoAtual,
                                    float dt,
                                    Direcao direcao,
                                    Vetor2 velocidadeMax) {
    Vetor2 novaPosicao = posicaoAtual;

    switch (direcao) {
    case CIMA:
        novaPosicao.y -= velocidadeMax.y * dt;
        break;

    case BAIXO:
        novaPosicao.y += velocidadeMax.y * dt;
        break;

    case DIREITA:
        novaPosicao.x += velocidadeMax.x * dt;
        break;

    case ESQUERDA:
        novaPosicao.x -= velocidadeMax.x * dt;
        break;
    }

    if ((int)novaPosicao.x > (int)posicaoAtual.x ||
        (parteFracao(novaPosicao.x) <= 0.05f && direcao == ESQUERDA)) {
        novaPosicao.x = floor(novaPosicao.x);
    }

    if ((int)novaPosicao.y > (int)posicaoAtual.y ||
        (parteFracao(novaPosicao.y) <= 0.05f && direcao == CIMA)) {
        novaPosicao.y = floor(novaPosicao.y);
    }

    return novaPosicao;
}
