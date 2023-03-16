#include "aplicacao.h"
#include "animacao.h"
#include "extra.h"
#include "mapa.h"
#include "textura.h"

#include <SDL.h>
#include <SDL_image.h>
#include <math.h>

static void atualizarMenu(Aplicacao *app, float dt) {
}

static void renderizarMenu(const Aplicacao *app) {
}

static void atualizarJogando(Aplicacao *app, float dt) {
    inputPacman(&app->pacman, &app->input);

    atualizarPacman(&app->pacman, dt, &app->mapa);
}

static void renderizarJogando(const Aplicacao *app) {
    renderizarMapa(&app->mapa, app->render);
    renderizarPacman(&app->pacman, &app->mapa, app->render);
}

static bool carregarJogoInicial(Aplicacao *app) {
    if (!carregarTilemap(&app->pacmanPng, app->render, "assets/pacman.png")) {
        SDL_Log("Falha em criar textura de tiles: %s\n", SDL_GetError());
        return false;
    }

    if (!preencherMapa(&app->mapa, app->render)) {
        SDL_Log("Falha em criar mapa de jogo: %s\n", mapaErro);
        return false;
    }

    app->pacmanPng.qtdTiles = (Point){11, 13};

    app->pacman.pontosColetados = 0;
    app->pacman.direcao  = CIMA;
    app->pacman.vidas    = 3;
    app->pacman.animacao = (Animacao){
        &app->pacmanPng,
        malloc(sizeof(int) * 3),
        3,
        3,
        24,
        0,
        true,
    };

    int tileL = TILE_LARGURA_MAPA(app->mapa);
    int tileA = TILE_ALTURA_MAPA(app->mapa);

    app->pacman.quinaEsquerdaSuperior = (Vetor2){10, 20};
    app->pacman.dimensoes             = (Point){tileL, tileA};

    for (int i = 0; i < 3; ++i) {
        app->pacman.animacao.tilemapValores[i] = 2 - i;
    }

    return true;
}

extern bool iniciarAplicacao(Aplicacao *app,
                             const char *titulo,
                             int largura,
                             int altura,
                             int flags) {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("falha em inicializar SDL: %s\n", SDL_GetError());
        return false;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        SDL_Log("falha em inicializar SDL_image: %s\n", SDL_GetError());
        return false;
    }

    app->janela = SDL_CreateWindow(titulo,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED,
                                   largura,
                                   altura,
                                   flags);

    if (!app->janela) {
        SDL_Log("falha em criar janela: %s\n", SDL_GetError());
        return false;
    }

    app->render = SDL_CreateRenderer(app->janela,
                                     -1,
                                     SDL_RENDERER_ACCELERATED |
                                         SDL_RENDERER_PRESENTVSYNC);

    if (!app->render) {
        SDL_Log("falha em criar SDL_Renderer: %s\n", SDL_GetError());
        return false;
    }

    app->fps    = 60.0f;
    app->estado = ESTADO_JOGANDO;

    SDL_SetRenderDrawColor(app->render, 0, 0, 0, 255);
    SDL_SetRenderDrawBlendMode(app->render, SDL_BLENDMODE_BLEND);

    if (!carregarJogoInicial(app)) {
        return false;
    }

    app->tempoPassado = SDL_GetTicks();

    return true;
}

extern void rodarAplicacao(Aplicacao *app) {
    const float milisegundosPorFrame = app->fps / 1000.0f;
    bool rodando                     = true;
    SDL_Event evento;

    while (rodando) {
        // Para limitar o FPS
        while (!SDL_TICKS_PASSED(SDL_GetTicks(),
                                 app->tempoPassado + milisegundosPorFrame)) {
        }

        // Calcula o tempo que passou desde ultimo frame
        float dt          = (SDL_GetTicks() - app->tempoPassado) * 0.001f;
        app->tempoPassado = SDL_GetTicks();

        inputReset(&app->input);

        while (SDL_PollEvent(&evento)) {
            if (evento.type == SDL_QUIT) {
                rodando = false;
            } else {
                // Sistemas de input salvam tudo que aconteceu em cada
                // frame(tecla pressionada, soltada etc)
                inputHandleEvent(&app->input, &evento);
            }
        }

        SDL_RenderClear(app->render);

        switch (app->estado) {
        case ESTADO_MENU:
            atualizarMenu(app, dt);
            renderizarMenu(app);
            break;

        case ESTADO_JOGANDO:
            atualizarJogando(app, dt);
            renderizarJogando(app);
            break;
        }

        SDL_RenderPresent(app->render);
    }
}

extern void deletarAplicacao(Aplicacao *app) {
    deletarTilemap(&app->pacmanPng);
    deletarAnimacao(&app->pacman.animacao);
    deletarMapa(&app->mapa);

    SDL_DestroyRenderer(app->render);
    SDL_DestroyWindow(app->janela);
    IMG_Quit();
    SDL_Quit();
}
