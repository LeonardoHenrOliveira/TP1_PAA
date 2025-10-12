#ifndef MAPA_H
#define MAPA_H

typedef struct {
    int D;          // durabilidade inicial
    int Dp;         // decremento por movimento
    int A;          // incremento por peça coletada
    int linhas;
    int colunas;
    char **mapa;    // matriz do mapa
    int **visitado; // matriz de visitados
    int **coletada; // matriz de peças coletadas
} Mundo;

// modo visual
extern int MODO_VISUAL;

// funções de mapa
int contarPecasRestantes(Mundo *m);
void mostrarMapa(Mundo *m, int atualL, int atualC);
void lerArquivo(Mundo *m, int *x_inicio, int *y_inicio);
void liberarMapa(Mundo *m);

#endif
