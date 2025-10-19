#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"
#include "Nave.h"

int main() {
    Mundo m;
    int x_inicio, y_inicio;
    char nomeArquivo[100];
    int continuar = 1;

    printf("==== PROJETO E ANALISE DE ALGORITMOS - TRABALHO 1 ====\n");

    while (continuar) {
        printf("\nDigite o nome do arquivo de entrada: ");
        scanf("%s", nomeArquivo);

        lerArquivo(&m, &x_inicio, &y_inicio, nomeArquivo);

        printf("Deseja ativar o modo visual (1 = sim, 0 = nao)? ");
        scanf("%d", &MODO_VISUAL);

        printf("Deseja ativar o modo de análise (1 = sim, 0 = nao)? ");
        scanf("%d", &MODO_ANALISE);

        iniciarJornada(&m, x_inicio, y_inicio);

        liberarMapa(&m);

        printf("\nDeseja executar outro teste? (1 = sim, 0 = nao): ");
        scanf("%d", &continuar);
    }

    printf("\nPrograma encerrado.\n");
    return 0;
}
