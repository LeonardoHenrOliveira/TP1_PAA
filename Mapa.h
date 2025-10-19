#ifndef MAPA_H
#define MAPA_H

typedef struct {
    int linhas, colunas;
    int D;  // Durabilidade inicial
    int Dp; // Durabilidade consumida por movimento
    int A;  // Durabilidade aumentada ao coletar peça
    char **mapa;
    int **visitado;
    int **coletada;
} Mundo;

extern int MODO_VISUAL;
extern int MODO_ANALISE;

void mostrarMapa(Mundo *m, int atualL, int atualC);
void lerArquivo(Mundo *m, int *x_inicio, int *y_inicio, const char *nomeArquivo);
void liberarMapa(Mundo *m);

#endif
