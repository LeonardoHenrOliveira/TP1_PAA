#ifndef MAPA_H
#define MAPA_H

typedef struct {
    int D, Dp, A;
    int linhas, colunas;
    char **mapa;
    int **visitado;
    int **coletada;
} Mundo;

extern int MODO_VISUAL;

int contarPecasRestantes(Mundo *m);
void mostrarMapa(Mundo *m, int atualL, int atualC);
void lerArquivo(Mundo *m, int *x_inicio, int *y_inicio);
void liberarMapa(Mundo *m);

#endif
