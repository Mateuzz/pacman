#include "extra.h"

#include <stdio.h>
#include <ctype.h>

char csvErro[200] = "";

extern int *carregarCSV(const char *arquivo, char separador, Point *qtd) {
    FILE *fp = fopen(arquivo, "r");

    if (!fp) {
        sprintf(csvErro, "não pode abrir %s", arquivo);
        return NULL;
    }

    int quantidade     = 0;
    int capacidade     = 100;
    bool primeiraLinha = true;
    Point tmpQtd       = {1, 0};
    int *csv = malloc(sizeof(int) * capacidade);
    int valor;
    char ch;

    if (!csv) {
        sprintf(csvErro, "falha de memória");
        return NULL;
    }

    for (;;) {
        if (fscanf(fp, "%d", &valor) != 1) {
            if (feof(fp)) {
                break;
            }
            sprintf(csvErro,
                    "formato de arquivo inválido, esperado número inteiro, size = (%d - %d)", tmpQtd.x, tmpQtd.y);
            free(csv);
            return NULL;
        }

        if (quantidade == capacidade) {
            capacidade += capacidade;
            if (!(csv = realloc(csv, sizeof(int) * capacidade))) {
                sprintf(csvErro, "falha de memória");
                return NULL;
            }
        }

        csv[quantidade++] = valor;

        for (;;) {
            fscanf(fp, "%c", &ch);

            if (ch == separador) {
                if (primeiraLinha) {
                    ++tmpQtd.x;
                }
                break;
            }

            if (ch == '\n' || ch == '\r') {
                ++tmpQtd.y;
                primeiraLinha = false;
                break;
            }
        }
    }

    if (quantidade != tmpQtd.x * tmpQtd.y) {
        sprintf(csvErro,
                "falha em analisar arquivo, quantidade de linhas e colunas "
                "inconsistentes");
        free(csv);
        return NULL;
    }

    *qtd = tmpQtd;

    return csv;
}
