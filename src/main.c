#define SDL_MAIN_HANDLED

#include "aplicacao.h"
#include "extra.h"

#include <stdlib.h>
#include <stdio.h>

/*
 * TODO
 * mapa.c => criar preencher mapa(funcao) gerar esquema de pontos e ligas para pathfind
 * colisao do pacman
 * berst first search algorithm
 * pacman
 * fantasmas com inteligencia artificial
 * menu do jogo
 */

int main(int argc, char **argv) {
    UNUSED_PARAMETER(argc);
    UNUSED_PARAMETER(argv);

    Aplicacao *app = malloc(sizeof(Aplicacao));
    
    if (!app) {
        fprintf(stderr, "Erro fatal, falha de memória\n");
        exit(EXIT_FAILURE);
    }

    if (iniciarAplicacao(app, "Pacman", 1024, 720, 0)) {
        rodarAplicacao(app);
    }

    deletarAplicacao(app);
    free(app);

    return 0;
}
