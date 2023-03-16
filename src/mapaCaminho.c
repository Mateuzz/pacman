#include "mapaCaminho.h"
#include "bool.h"
#include <stdlib.h>

typedef struct {
    NoGrafoMapa *no;
    bool foiVerificado;
} NoGrafoMapaCaminho;

extern void buscarCaminhoGrafo(const GrafoMapa *grafo,
                               const NoGrafoMapa *comeco,
                               const NoGrafoMapa *destino) {
    NoGrafoMapaCaminho *nos = malloc(grafo->qtdTiles.x * grafo->qtdTiles.y * sizeof(NoGrafoMapaCaminho));
}
