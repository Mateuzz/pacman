#include "mapa.h"
#include "SDL_error.h"
#include "animacao.h"
#include "extra.h"
#include "point.h"
#include "textura.h"
#include "tilemap.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

char mapaErro[200] = "";

static bool carregarTexturaMapa(SDL_Texture **textura,
                                const char *arquivo,
                                SDL_Renderer *render) {
    if (!(*textura = carregarTextura(render, arquivo))) {
        strcpy(csvErro, SDL_GetError());
        return false;
    }
    return true;
}

static void criarAdjacente(const GrafoMapa *grafo, Point posicao) {
    const Point adjacentesIndexes[MAX_NOGRAFO_ADJACENTES] = {
        {posicao.x, posicao.y - 1},
        {posicao.x + 1, posicao.y},
        {posicao.x + 1, posicao.y + 1},
        {posicao.x - 1, posicao.y},
    };

    NoGrafoMapa *no = &GRAFO_NO(*grafo, posicao.y, posicao.x);

    no->numeroAdjacentes = 0;

    for (int i = 0; i < MAX_NOGRAFO_ADJACENTES; ++i) {
        NoGrafoMapa *noAdjacente =
            noGrafoNaPosicao(adjacentesIndexes[i], grafo);

        if (noAdjacente) {
            no->adjacentes[no->numeroAdjacentes++] = noAdjacente;
        }
    }
}

extern NoGrafoMapa *noGrafoNaPosicao(Point posicao, const GrafoMapa *grafo) {
    return ((unsigned)posicao.x < (unsigned)grafo->qtdTiles.x &&
            (unsigned)posicao.y < (unsigned)grafo->qtdTiles.y)
               ? &GRAFO_NO(*grafo, posicao.y, posicao.x)
               : NULL;
}

extern void criarGrafo(const GrafoMapa *grafo) {
    for (int y = 0; y < grafo->qtdTiles.y; ++y) {
        for (int x = 0; x < grafo->qtdTiles.x; ++x) {
            criarAdjacente(grafo, (Point){x, y});
        }
    }
}

static void criarTipoNoPorValorCsv(NoGrafoMapa *no,
                                   int valorBase,
                                   int valorExtra,
                                   int valorPonto) {
    switch (valorBase) {
    case 81:
        no->tipo.tipo = TIPO_QUINA;
        break;

    case 132:
        no->tipo.tipo = TIPO_ESPACO_VAZIO;
        break;
    }

    switch (valorExtra) {
    case 65:
        no->tipo.tipo = TIPO_QUINA_PORTA_FANTASMA;
        break;
    }

    switch (valorPonto) {
    case 34:
        no->tipo.items = MAPA_ITEM_PONTO;
        break;

    case 102:
        no->tipo.items = MAPA_ITEM_PONTO_ENERGIZANTE;
        break;

    case -1:
        no->tipo.items = 0;
        break;

    default:
        assert(false);
    }
}

extern bool preencherGrafoMapa(GrafoMapa *grafo, const char *const *arquivos) {
    Point qtds[NUM_ARQUIVOS];
    int *csvs[NUM_ARQUIVOS];

    for (int i = 0; i < NUM_ARQUIVOS; ++i) {
        if (!(csvs[i] = carregarCSV(arquivos[i], ',', &qtds[i]))) {
            strcpy(mapaErro, csvErro);
            return false;
        }
    }

    assert(qtds[0].x == qtds[1].x);
    assert(qtds[0].y == qtds[1].y);
    assert(qtds[2].x == qtds[1].x);
    assert(qtds[2].y == qtds[1].y);

    if (!(grafo->tiles = malloc(sizeof(NoGrafoMapa) * qtds[0].x * qtds[0].y))) {
        return false;
    }

    for (int i = 0; i < qtds[0].y; ++i) {
        for (int j = 0; j < qtds[0].x; ++j) {
            int n = i * qtds[0].x + j;

            criarTipoNoPorValorCsv(&grafo->tiles[n],
                                   csvs[ARQUIVO_BASE][n],
                                   csvs[ARQUIVO_EXTRA][n],
                                   csvs[ARQUIVO_PONTOS][n]);
        }
    }

    grafo->qtdTiles = qtds[ARQUIVO_BASE];

    for (int i = 0; i < NUM_ARQUIVOS; ++i) {
        free(csvs[i]);
    }

    criarGrafo(grafo);

    return true;
}

extern bool preencherMapa(Mapa *mapa, SDL_Renderer *render) {
    const char *arquivos[NUM_ARQUIVOS] = {
        "assets/mapaBase.csv",
        "assets/mapaExtra.csv",
        "assets/mapaPontos.csv",
    };

    mapa->posicao = (Point){250, 30};

    if (!carregarTexturaMapa(&mapa->textura, "assets/mapa.png", render)) {
        return false;
    }

    if (!carregarTilemap(&mapa->texturasExtra, render, "assets/extra.png")) {
        strcpy(mapaErro, SDL_GetError());
        return false;
    }

    mapa->texturasExtra.qtdTiles = (Point){16, 11};

    if (!preencherGrafoMapa(&mapa->grafo, arquivos)) {
        return false;
    }

    SDL_QueryTexture(mapa->textura,
                     NULL,
                     NULL,
                     &mapa->dimensoes.x,
                     &mapa->dimensoes.y);

    mapa->dimensoes.x *= 1.5f;
    mapa->dimensoes.y *= 1.5f;

    return true;
}

extern void renderizarMapa(const Mapa *mapa, SDL_Renderer *render) {
    SDL_Rect destino = {mapa->posicao.x,
                        mapa->posicao.y,
                        mapa->dimensoes.x,
                        mapa->dimensoes.y};

    SDL_RenderCopy(render, mapa->textura, NULL, &destino);

    Point tileDimensoes = {TILE_LARGURA_MAPA(*mapa), TILE_ALTURA_MAPA(*mapa)};

    static struct {
        int valor;
        int flag;
    } valoresTilesETipos[] = {
        {34, MAPA_ITEM_PONTO},
        {102, MAPA_ITEM_PONTO_ENERGIZANTE},
    };

    for (int i = 0; i < mapa->grafo.qtdTiles.y; ++i) {
        for (int j = 0; j < mapa->grafo.qtdTiles.x; ++j) {
            int n = i * mapa->grafo.qtdTiles.x + j;

            for (int k = 0; k < SIZE_ARRAY(valoresTilesETipos); ++k) {
                if (HAS_FLAG(mapa->grafo.tiles[n].tipo.items,
                             valoresTilesETipos[k].flag)) {
                    destino = (SDL_Rect){j * tileDimensoes.x + mapa->posicao.x,
                                         i * tileDimensoes.y + mapa->posicao.y,
                                         tileDimensoes.x,
                                         tileDimensoes.y};

                    renderizarTile(&mapa->texturasExtra,
                                   valoresTilesETipos[k].valor,
                                   render,
                                   &destino,
                                   0);
                    break;
                }
            }
        }
    }
}

extern void deletarMapa(Mapa *mapa) {
    free(mapa->grafo.tiles);
    deletarTilemap(&mapa->texturasExtra);
    SDL_DestroyTexture(mapa->textura);
}

extern bool colideMapa(const Mapa *mapa, Vetor2 posTile, int tiposColidiveis) {
    struct{
        Vetor2 tile;
        bool deveVerificar;
    } tilesParaAnalisar[] = {
        {{posTile.x, posTile.y}, true},
        {{posTile.x + 1, posTile.y}, false},
        {{posTile.x, posTile.y + 1}, false},
        {{posTile.x + 1, posTile.y + 1}, false},
    };

    // entao verifica da direita
    if (posTile.x != (int)posTile.x) {
        tilesParaAnalisar[1].deveVerificar = true;

        // verifica tile do canto da direita em baixo
        if (posTile.y != (int)posTile.y) {
            tilesParaAnalisar[3].deveVerificar = true;
        }
    }

    // entao verifica tile de baixo
    if (posTile.y != (int)posTile.y) {
        tilesParaAnalisar[2].deveVerificar = true;
    }

    for (int i = 0; i < SIZE_ARRAY(tilesParaAnalisar); ++i) {
        if (tilesParaAnalisar[i].deveVerificar) {
            Point paraAnalisar = {
                tilesParaAnalisar[i].tile.x,
                tilesParaAnalisar[i].tile.y,
            };

            const NoGrafoMapa *no =
                noGrafoNaPosicao(paraAnalisar, &mapa->grafo);

            if (no && HAS_FLAG(no->tipo.tipo, tiposColidiveis)) {
                return true;
            }
        }
    }

    return false;
}

extern void
obterPosicaoDentroDoMapa(const Mapa *mapa, Vetor2 posTile, Vetor2 *posReal) {
    posReal->x = posTile.x * TILE_LARGURA_MAPA(*mapa) + mapa->posicao.x;
    posReal->y = posTile.y * TILE_ALTURA_MAPA(*mapa) + mapa->posicao.y;
}

extern void renderizarAnimacaoNoMapa(const Mapa *mapa,
                                     SDL_Renderer *render,
                                     const Animacao *animacao,
                                     Vetor2 posicaoTile,
                                     Point dimensoes,
                                     float angulo) {
    obterPosicaoDentroDoMapa(mapa, posicaoTile, &posicaoTile);

    SDL_Rect destino = {
        posicaoTile.x,
        posicaoTile.y,
        dimensoes.x,
        dimensoes.y,
    };

    renderizarAnimacao(animacao, render, &destino, angulo);
}

extern Point tileDoCentro(Vetor2 posTile) {
    Point tile = {posTile.x, posTile.y};

    if (parteFracao(posTile.x) > 0.5f) {
        ++tile.x;
    }
    if (parteFracao(posTile.y) > 0.5f) {
        ++tile.y;
    }

    return tile;
}

extern bool moverPersonagem(const Mapa *mapa,
                            Vetor2 *posicao,
                            Vetor2 velocidadeMax,
                            Direcao direcao,
                            int tileColidiveis,
                            float dt) {
    Vetor2 novaPosicao =
        novaPosicaoPersonagem(*posicao, dt, direcao, velocidadeMax);

    if (colideMapa(mapa, novaPosicao, tileColidiveis)) {
        return false;
    }

    *posicao = novaPosicao;

    return true;
}


