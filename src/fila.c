#include "fila.h"

#include <stdlib.h>

extern Fila *criarFila(void) {
    return calloc(1, sizeof(Fila));
}

extern ItemFila *novoItemFila(void) {
    return malloc(sizeof(ItemFila));
}

extern void adicionarItemFila(Fila *fila, ItemFila *item) {
    if (!fila->primeiro) {
        fila->primeiro = item;
    } else {
        fila->ultimo->atras = item;
    }

    item->frente = fila->ultimo;
    fila->ultimo = item;
    ++fila->tamanho;
    item->atras = NULL;
}

extern void removeDaFila(Fila *fila) {
    ItemFila *removido = fila->primeiro;
    fila->primeiro = fila->primeiro->atras;
    if (fila->primeiro){
        fila->primeiro->frente = NULL;
    }
    --fila->tamanho;
    free(removido);
}

extern bool filaVazia(const Fila *fila) {
    return !fila->primeiro;
}

extern void esvaziarFila(Fila *fila) {
    ItemFila *atual = fila->primeiro;
    ItemFila *frente;

    while (atual) {
        frente = atual;
        atual = atual->atras;
        free(frente);
    }

    fila->primeiro = fila->ultimo = NULL;
    fila->tamanho = 0;
}

extern void destruirFila(Fila *fila) {
    esvaziarFila(fila);
    free(fila);
}
