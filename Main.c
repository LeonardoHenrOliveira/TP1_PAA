#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"
#include "Nave.h"

int main() {
    Mundo m;
    int x_inicio, y_inicio;

    // Ler mapa e parâmetros do arquivo
    lerArquivo(&m, &x_inicio, &y_inicio);

    // Escolher modo visual
    printf("Deseja ativar o modo visual (1 = sim, 0 = nao)? ");
    scanf("%d", &MODO_VISUAL);

    // Iniciar jornada a partir do ponto inicial marcado com 'X'
    iniciarJornada(&m, x_inicio, y_inicio);

    // Liberar memória
    liberarMapa(&m);

    return 0;
}
