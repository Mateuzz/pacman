#pragma once

#include "mapa.h"

#include <stdbool.h>
#include <stddef.h>

#define NOVO_ITEM_FILA() (malloc(sizeof(ItemFila)))

typedef struct Fila Fila;
typedef struct ItemFila ItemFila;
typedef NoGrafoMapa *ValorFila;

struct ItemFila {
    ValorFila valor;
    struct ItemFila *atras;
    struct ItemFila *frente;
};

struct Fila {
    ItemFila *primeiro;
    ItemFila *ultimo;
    size_t tamanho;
};

extern Fila *criarFila(void);
extern ItemFila *novoItemFila(void);
extern void adicionarItemFila(Fila *fila, ItemFila *item);
extern void removeDaFila(Fila *fila);
extern void esvaziarFila(Fila *fila);
extern void destruirFila(Fila *fila);
