#include <stdio.h>
#include "Mapa.h"
#include "Nave.h"

int main() {
    Mundo m;
    int x_inicio, y_inicio;

    lerArquivo(&m, &x_inicio, &y_inicio);

    printf("Deseja ativar o modo visual (1=sim, 0=nao)? ");
    scanf("%d", &MODO_VISUAL);

    // Chama a jornada completa (controla recursão, peças e fim automático)
    iniciarJornada(&m, x_inicio, y_inicio);

    liberarMapa(&m);
    return 0;
}
