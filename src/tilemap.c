#include "tilemap.h"
#include "textura.h"

#include <assert.h>

extern bool
carregarTilemap(Tilemap *tilemap, SDL_Renderer *render, const char *arquivo) {
    tilemap->textura = carregarTextura(render, arquivo);

    if (!tilemap->textura) {
        return false;
    }

    SDL_QueryTexture(tilemap->textura,
                     NULL,
                     NULL,
                     &tilemap->texturaDimensoes.x,
                     &tilemap->texturaDimensoes.y);

    return true;
}

extern SDL_Rect
obterTileDestino(const Tilemap *tilemap, Point xy, float escala) {
    int tileLargura = TILE_LARGURA(*tilemap);
    int tileAltura  = TILE_ALTURA(*tilemap);

    return (SDL_Rect){xy.x, xy.y, tileLargura * escala, tileAltura * escala};
}

extern void renderizarTile(const Tilemap *tilemap,
                           int valor,
                           SDL_Renderer *render,
                           const SDL_Rect *destino,
                           float anguloGraus) {
    assert(tilemap->textura != NULL);

    int tileLargura = TILE_LARGURA(*tilemap);
    int tileAltura  = TILE_ALTURA(*tilemap);

    int posicaoY = valor % tilemap->qtdTiles.x;
    int posicaoX = valor / tilemap->qtdTiles.x;

    SDL_Rect tile = {tileLargura * posicaoY,
                     tileAltura * posicaoX,
                     tileLargura,
                     tileAltura};

    SDL_RenderCopyEx(render,
                     tilemap->textura,
                     &tile,
                     destino,
                     -anguloGraus,
                     NULL,
                     SDL_FLIP_NONE);
}

extern void deletarTilemap(Tilemap *tilemap) {
    SDL_DestroyTexture(tilemap->textura);
    tilemap->textura = NULL;
}

extern SDL_Texture *criarTexturaDeMapa(const Tilemap *tilemap,
                                       const int *valoresTiles,
                                       Point qtdTiles,
                                       SDL_Renderer *render,
                                       Point tamanhoTextura) {
    SDL_Texture *textura = SDL_CreateTexture(render,
                                             SDL_PIXELFORMAT_RGBA8888,
                                             SDL_TEXTUREACCESS_TARGET,
                                             tamanhoTextura.x,
                                             tamanhoTextura.y);
    if (!textura) {
        return NULL;
    }

    SDL_SetRenderTarget(render, textura);
    SDL_SetRenderDrawBlendMode(render, SDL_BLENDMODE_BLEND);

    Point tileDimensoesFonte = {
        TILE_LARGURA(*tilemap),
        TILE_ALTURA(*tilemap),
    };

    Point tileDimensoesDestino = {tamanhoTextura.x / qtdTiles.x,
                                  tamanhoTextura.y / qtdTiles.y};

    for (int y = 0; y < qtdTiles.y; ++y) {
        for (int x = 0; x < qtdTiles.x; ++x) {
            int valorTile = valoresTiles[y * qtdTiles.x + x];

            Point posicaoTile = {valorTile % tilemap->qtdTiles.x,
                                 valorTile / tilemap->qtdTiles.x};

            SDL_Rect fonte = {posicaoTile.x * tileDimensoesFonte.x,
                              posicaoTile.y * tileDimensoesFonte.y,
                              tileDimensoesFonte.x,
                              tileDimensoesFonte.y};

            SDL_Rect destino = {x * tileDimensoesDestino.x,
                                y * tileDimensoesDestino.y,
                                tileDimensoesDestino.x,
                                tileDimensoesDestino.y};

            SDL_RenderCopy(render, tilemap->textura, &fonte, &destino);
        }
    }

    SDL_SetRenderTarget(render, NULL);

    return textura;
}
