#include "Leitura_Arquivo.h"
#include "Entradas_Extras/Gerar_Testes.h"

int main() {
    char nome_arquivo[256];

    printf("Digite o nome do arquivo de entrada: ");
    if (scanf("%255s", nome_arquivo) != 1) {
        printf("Entrada invalida.\n");
        return 1;
    }

    // Gera um mapa de teste
    //gerar_mapa_teste("../Entradas/mapa_teste.txt",
    //                  20, 5, 10,   // D, D’, A
    //                  7, 10,       // altura, largura
    //                  4);          // número de peças

    Mapa *m = mapa_ler_de_arquivo(nome_arquivo);

    mapa_imprimir_relatorio(m);

    mapa_liberar(m);
    return 0;
}