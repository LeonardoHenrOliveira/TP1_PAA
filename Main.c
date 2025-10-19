#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"
#include "Nave.h"
#include "Entradas_Extras/Gerar_Testes.h"  // Inclua se o gerador estiver nessa pasta

int main() {
    Mundo m;
    int x_inicio, y_inicio;
    char nomeArquivo[100];
    int continuar = 1;
    int opcao;

    printf("==== PROJETO E ANÁLISE DE ALGORITMOS - TRABALHO 1 ====\n");

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

        printf("\nDeseja criar um teste extra? (1 = sim, 0 = nao): ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            char nomeTeste[100];
            printf("Digite o nome do arquivo de teste (ex: teste.txt): ");
            scanf("%s", nomeTeste);

            int durabilidade, custo_mov, bonus_peca;
            int linhas, colunas, num_pecas, dificuldade;

            printf("\n=== Configuração do mapa de teste ===\n");
            printf(" - Durabilidade inicial (1–1000): ");
            scanf("%d", &durabilidade);

            printf(" - Custo de movimento (1–100): ");
            scanf("%d", &custo_mov);

            printf(" - Bônus por peça (1–500): ");
            scanf("%d", &bonus_peca);

            printf(" - Altura do mapa (5–50): ");
            scanf("%d", &linhas);

            printf(" - Largura do mapa (5–50): ");
            scanf("%d", &colunas);

            printf(" - Quantidade de peças (1–%d): ", (linhas * colunas) / 5);
            scanf("%d", &num_pecas);

            printf(" - Dificuldade (0–10): ");
            scanf("%d", &dificuldade);

            gerar_mapa_teste(nomeTeste,
                             durabilidade, custo_mov, bonus_peca,
                             linhas, colunas, num_pecas, dificuldade);

            printf("✅ Arquivo de teste '%s' criado com sucesso!\n", nomeTeste);
        }

        printf("\nDeseja executar outro teste? (1 = sim, 0 = nao): ");
        scanf("%d", &continuar);
    }

    printf("\nPrograma encerrado.\n");
    return 0;
}
