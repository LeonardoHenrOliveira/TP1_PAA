/* main.c */
#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"
#include "Nave.h"

int main() {
    Mundo m;
    int x, y;

    lerArquivo(&m, &x, &y);                // primeiro leia o mapa e obtenha x,y

    x_inicio_global = x;                   // agora atribua às globais
    y_inicio_global = y;

    printf("Deseja ativar o modo visual (1=sim, 0=nao)? ");
    scanf("%d", &MODO_VISUAL);

    movimentar(&m, x, y, m.D, 1);

    if (!achou_destino)
        printf("\nApesar da bravura, a tripulação falhou em sua jornada.\n");

    printf("\nChamadas recursivas: %d\n", chamadas_recursivas);
    printf("Nível máximo de recursão: %d\n", max_nivel_recursao);

    liberarMapa(&m);
    return 0;
}
