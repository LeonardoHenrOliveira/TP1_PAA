#include <stdio.h>
#include "Mapa.h"
#include "Nave.h"

int main() {
    Mundo m;
    int x_inicio, y_inicio;

    lerArquivo(&m, &x_inicio, &y_inicio);

    printf("Deseja ativar o modo visual (1=sim, 0=nao)? ");
    scanf("%d", &MODO_VISUAL);

    chamadas_recursivas = 0;
    max_nivel_recursao = 0;
    achou_destino = 0;

    movimentar(&m, x_inicio, y_inicio, m.D, 1, 4); // sempre 4 peças necessárias

    if (!achou_destino)
        printf("\nApesar da bravura, a tripulação falhou em sua jornada.\n");

    printf("\nChamadas recursivas: %d\n", chamadas_recursivas);
    printf("Nível máximo de recursão: %d\n", max_nivel_recursao);

    liberarMapa(&m);
    return 0;
}
