#ifndef MAPA_H
#define MAPA_H

typedef struct {
    int D, Dp, A;
    int linhas, colunas;
    char **mapa;
    int **visitado;
    int **coletada;
} Mundo;

void lerArquivo(Mundo *m, int *x_inicio, int *y_inicio);
void mostrarMapa(Mundo *m, int atualL, int atualC);
int contarPecasRestantes(Mundo *m);
void liberarMapa(Mundo *m);

extern int MODO_VISUAL;

#endif
