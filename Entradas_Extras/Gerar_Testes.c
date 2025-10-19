#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void gerar_mapa_teste(const char *caminho_arquivo,
                      int durabilidade, int custo_mov, int bonus_peca,
                      int altura, int largura, int num_pecas, int dificuldade) {
    FILE *f = fopen(caminho_arquivo, "w");
    if (!f) { perror("Erro ao abrir arquivo"); return; }

    srand(time(NULL));

    // Cabeçalho
    fprintf(f, "%d %d %d\n", durabilidade, custo_mov, bonus_peca);
    fprintf(f, "%d %d\n", altura, largura);

    // Cria mapa base vazio
    char **mapa = malloc(altura * sizeof(char *));
    for (int i = 0; i < altura; i++) {
        mapa[i] = malloc((largura + 1) * sizeof(char));
        for (int j = 0; j < largura; j++) mapa[i][j] = '.';
        mapa[i][largura] = '\0';
    }

    // Posição inicial X
    int xr = rand() % altura;
    int xc = rand() % largura;
    mapa[xr][xc] = 'X';

    // Destino F
    int fr = rand() % altura;
    int fc = rand() % largura;
    while (fr == xr && fc == xc) fc = rand() % largura;
    mapa[fr][fc] = 'F';

    // Cria caminho garantido de X até F
    int cx = xr, cy = xc;
    while (cx != fr || cy != fc) {
        if (cx != fr) {
            cx += (fr > cx) ? 1 : -1;
            mapa[cx][cy] = '-'; // caminho horizontal/vertical
        } else if (cy != fc) {
            cy += (fc > cy) ? 1 : -1;
            mapa[cx][cy] = '|';
        }
    }
    mapa[xr][xc] = 'X';
    mapa[fr][fc] = 'F';

    // Adiciona obstáculos aleatórios sem bloquear o caminho
    int prob_parede = dificuldade * 10; // 0..100%
    for (int i = 0; i < altura; i++) {
        for (int j = 0; j < largura; j++) {
            if (mapa[i][j] == '.') {
                int r = rand() % 100;
                if (r < prob_parede) {
                    int tipo = rand() % 3;
                    mapa[i][j] = (tipo == 0) ? '-' : (tipo == 1) ? '|' : '+';
                }
            }
        }
    }

    // Adiciona peças (P)
    for (int k = 0; k < num_pecas; k++) {
        int pr, pc;
        do {
            pr = rand() % altura;
            pc = rand() % largura;
        } while (mapa[pr][pc] != '.');
        mapa[pr][pc] = 'P';
    }

    // Escreve mapa
    for (int i = 0; i < altura; i++) {
        fprintf(f, "%s\n", mapa[i]);
        free(mapa[i]);
    }
    free(mapa);
    fclose(f);

    printf("Mapa de teste gerado com sucesso em '%s'.\n", caminho_arquivo);
}
