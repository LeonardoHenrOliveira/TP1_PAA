#include "Gerar_Testes.h"

void gerar_mapa_teste(const char *caminho_arquivo,
                      int durabilidade, int custo_mov, int bonus_peca,
                      int altura, int largura, int num_pecas) {
    FILE *f = fopen(caminho_arquivo, "w");
    if (!f) {
        return;
    }

    srand(time(NULL));

    fprintf(f, "%d %d %d\n", durabilidade, custo_mov, bonus_peca);
    // Dimensões
    fprintf(f, "%d %d\n", altura, largura);

    char **mapa = malloc(altura * sizeof(char *));
    for (int i = 0; i < altura; i++) {
        mapa[i] = malloc((largura + 1) * sizeof(char));
        for (int j = 0; j < largura; j++) {
            mapa[i][j] = '.';
        }
        mapa[i][largura] = '\0';
    }

    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            int tipo = rand() % 10;
            if (tipo < 4)
                mapa[i][j] = '-';
            else if (tipo < 7)
                mapa[i][j] = '|';
            else if (tipo == 7)
                mapa[i][j] = '+';
        }
    }

    // Adiciona posição inicial (X)
    int xr = rand() % altura;
    int xc = rand() % largura;
    mapa[xr][xc] = 'X';

    // Adiciona destino (F)
    int fr, fc;
    do {
        fr = rand() % altura;
        fc = rand() % largura;
    } while (mapa[fr][fc] == 'X');
    mapa[fr][fc] = 'F';

    // Adiciona peças (P)
    for (int k = 0; k < num_pecas; k++) {
        int pr, pc;
        do {
            pr = rand() % altura;
            pc = rand() % largura;
        } while (mapa[pr][pc] != '.');
        mapa[pr][pc] = 'P';
    }

    // Escreve mapa no arquivo
    for (int i = 0; i < altura; i++) {
        fprintf(f, "%s\n", mapa[i]);
        free(mapa[i]);
    }
    free(mapa);

    fclose(f);

    printf("Mapa gerado com sucesso ");
}