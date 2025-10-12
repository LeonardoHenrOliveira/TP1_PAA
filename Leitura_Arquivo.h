#ifndef LEITURA_ARQUIVO_H
#define LEITURA_ARQUIVO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct {
    int D;          
    int dec;
    int A;
    int h;
    int w;
    char **grid;
    int start_r;
    int start_c;
    int total_p;    
} Mapa;


Mapa *mapa_ler_de_arquivo(const char *nome_arquivo);
void mapa_imprimir_relatorio(const Mapa *m);    
void mapa_liberar(Mapa *m);

#endif 