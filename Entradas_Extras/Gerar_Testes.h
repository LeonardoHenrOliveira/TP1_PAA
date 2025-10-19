#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifndef GERAR_TESTES_H
#define GERAR_TESTES_H

/* Assinatura da função — 8 parâmetros (atenção à ordem) */
void gerar_mapa_teste(const char *caminho_arquivo,
                      int durabilidade, int custo_mov, int bonus_peca,
                      int altura, int largura, int num_pecas, int dificuldade);


#endif /* GERAR_TESTES_H */
