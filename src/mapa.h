#pragma once

#include "animacao.h"
#include "point.h"
#include "tilemap.h"
#include <stddef.h>

#define GRAFO_NO(grafo, i, j)  ((grafo).tiles[((i) * (grafo).qtdTiles.x + (j))])
#define MAX_NOGRAFO_ADJACENTES 4

#define TILE_LARGURA_MAPA(mapa) ((mapa).dimensoes.x / (mapa).grafo.qtdTiles.x)
#define TILE_ALTURA_MAPA(mapa)  ((mapa).dimensoes.y / (mapa).grafo.qtdTiles.y)

enum Arquivo { ARQUIVO_BASE, ARQUIVO_EXTRA, ARQUIVO_PONTOS, NUM_ARQUIVOS };

typedef struct {
    enum MapaItem {
        MAPA_ITEM_PONTO             = 0x00000001,
        MAPA_ITEM_PONTO_ENERGIZANTE = 0x00000002,
        MAPA_ITEM_FRUTA             = 0x00000004,
    } items;

    enum Tipo {
        TIPO_QUINA                = 0x00000001,
        TIPO_ESPACO_VAZIO         = 0x00000002,
        TIPO_QUINA_PORTA_FANTASMA = 0x00000004
    } tipo;
} Mapatile;

typedef struct NoGrafoMapa {
    struct NoGrafoMapa *adjacentes[MAX_NOGRAFO_ADJACENTES];
    Mapatile tipo;
    int numeroAdjacentes;
} NoGrafoMapa;

typedef struct {
    NoGrafoMapa *tiles;
    Point qtdTiles;
} GrafoMapa;

typedef struct {
    SDL_Texture *textura;
    Tilemap texturasExtra;
    GrafoMapa grafo;
    Point dimensoes;
    Point posicao;
} Mapa;

extern char mapaErro[200];

// criar um mapa com base num arquivo de formato especificado
extern bool preencherMapa(Mapa *mapa, SDL_Renderer *render);

extern bool preencherGrafoMapa(GrafoMapa *grafo, const char *const *arquivos);

extern void renderizarMapa(const Mapa *mapa, SDL_Renderer *render);

extern void deletarMapa(Mapa *mapa);

// Criar as conexões adjacentes nos nós de um GrafoMapa já inicializado
extern void criarGrafo(const GrafoMapa *grafo);

// retorna um ponteiro para um determinado no numa posicao,
// retorna NULL se nao existir
extern NoGrafoMapa *noGrafoNaPosicao(Point posicao, const GrafoMapa *grafo);

extern bool colideMapa(const Mapa *mapa, Vetor2 posTile, int tiposColidiveis);

extern void
obterPosicaoDentroDoMapa(const Mapa *mapa, Vetor2 posTile, Vetor2 *posReal);

extern void renderizarAnimacaoNoMapa(const Mapa *mapa,
                                     SDL_Renderer *render,
                                     const Animacao *animacao,
                                     Vetor2 posicaoTile,
                                     Point dimensoes,
                                     float angulo);

extern Point tileDoCentro(Vetor2 posTile);

extern bool moverPersonagem(const Mapa *mapa,
                            Vetor2 *posicao,
                            Vetor2 velocidadeMax,
                            Direcao direcao,
                            int tileColidiveis,
                            float dt);

SDL_FORCE_INLINE Point posicaoGrafoNo(const GrafoMapa *grafo,
                                      const NoGrafoMapa *no) {
    ptrdiff_t posicao = no - grafo->tiles;
    return (Point){posicao % grafo->qtdTiles.x, posicao / grafo->qtdTiles.x};
}
