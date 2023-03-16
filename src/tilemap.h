#pragma once

#include "bool.h"
#include "point.h"

#include <SDL.h>

#define TILE_LARGURA(tilemap)                                                  \
    ((tilemap).texturaDimensoes.x / (tilemap).qtdTiles.x)
#define TILE_ALTURA(tilemap)                                                   \
    ((tilemap).texturaDimensoes.y / (tilemap).qtdTiles.y)

typedef struct {
    Point texturaDimensoes;
    Point qtdTiles;
    SDL_Texture *textura;
} Tilemap;

typedef struct {
    Tilemap *tilemap;
    int valor;
} Tile;

extern bool
carregarTilemap(Tilemap *tilemap, SDL_Renderer *render, const char *arquivo);

extern void renderizarTile(const Tilemap *tilemap,
                           int valor,
                           SDL_Renderer *render,
                           const SDL_Rect *destino,
                           float anguloGraus);

extern SDL_Rect
obterTileDestino(const Tilemap *tilemap, Point xy, float escala);

extern SDL_Texture *criarTexturaDeMapa(const Tilemap *tilemap,
                                       const int *valoresTiles,
                                       Point qtdTiles,
                                       SDL_Renderer *render,
                                       Point tamanhoTextura);

extern void deletarTilemap(Tilemap *tilemap);
