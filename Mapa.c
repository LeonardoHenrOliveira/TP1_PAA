#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Mapa.h"

int MODO_VISUAL = 1; // 1 = modo visual, 0 = modo silencioso

void mostrarMapa(Mundo *m, int atualL, int atualC) {
    if (!MODO_VISUAL) return;

    printf("\n===== MAPA ATUAL =====\n");
    for (int i = 0; i < m->linhas; i++) {
        for (int j = 0; j < m->colunas; j++) {
            if (i == atualL && j == atualC)
                printf("\033[1;32mX\033[0m");
            else if (m->visitado[i][j])
                printf("\033[1;34m%c\033[0m", m->mapa[i][j]);
            else
                printf("%c", m->mapa[i][j]);
        }
        printf("\n");
    }
    printf("=======================\n");
    usleep(300000); // 0,3s de delay
}

void lerArquivo(Mundo *m, int *x_inicio, int *y_inicio) {
    FILE *arq = fopen("entrada.txt", "r");
    if (!arq) {
        printf("Erro ao abrir o arquivo!\n");
        exit(1);
    }

    fscanf(arq, "%d %d %d", &m->D, &m->Dp, &m->A);
    fscanf(arq, "%d %d", &m->linhas, &m->colunas);

    m->mapa = malloc(m->linhas * sizeof(char *));
    m->visitado = malloc(m->linhas * sizeof(int *));
    m->coletada = malloc(m->linhas * sizeof(int *));
    for (int i = 0; i < m->linhas; i++) {
        m->mapa[i] = malloc((m->colunas + 1) * sizeof(char));
        m->visitado[i] = calloc(m->colunas, sizeof(int));
        m->coletada[i] = calloc(m->colunas, sizeof(int));
        fscanf(arq, "%s", m->mapa[i]);
        for (int j = 0; j < m->colunas; j++) {
            if (m->mapa[i][j] == 'X') {
                *x_inicio = i;
                *y_inicio = j;
            }
        }
    }
    fclose(arq);
}

void liberarMapa(Mundo *m) {
    for (int i = 0; i < m->linhas; i++) {
        free(m->mapa[i]);
        free(m->visitado[i]);
        free(m->coletada[i]);
    }
    free(m->mapa);
    free(m->visitado);
    free(m->coletada);
}
