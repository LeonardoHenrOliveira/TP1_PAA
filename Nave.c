#include <stdio.h>
#include "Mapa.h"
#include "Nave.h"

int chamadas_recursivas = 0;
int max_nivel_recursao = 0;
int achou_destino = 0;

int movimentos[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

int podeMover(char atual, char prox, int dir) {
    if (prox == '.' || prox == '\0') return 0;
    if (prox == 'P' || prox == 'F' || prox == '+') return 1;
    if (prox == '-' && (dir == 2 || dir == 3)) return 1;
    if (prox == '|' && (dir == 0 || dir == 1)) return 1;
    return 0;
}

void movimentar(Mundo *m, int l, int c, int dur, int nivel, int pecas_restantes) {
    chamadas_recursivas++;
    if (nivel > max_nivel_recursao) max_nivel_recursao = nivel;

    m->visitado[l][c] = 1;

    // Coleta peça
    if (m->mapa[l][c] == 'P' && m->coletada[l][c] == 0) {
        m->coletada[l][c] = 1;
        dur += m->A;
        pecas_restantes--;
        if (pecas_restantes < 0) pecas_restantes = 0;
    }

    mostrarMapa(m, l, c);
    printf("Linha: %d, Coluna: %d; D: %d, peças restantes: %d\n",
           l+1, c+1, dur, pecas_restantes);

    // Chegou ao destino
    if (m->mapa[l][c] == 'F') {
        achou_destino = 1;
        if (pecas_restantes == 0)
            printf("\nA jornada será finalizada sem mais desafios.\n");
        else
            printf("\nA tripulação finalizou sua jornada.\n");
        return;
    }

    if (dur <= 0) return;

    for (int i = 0; i < 4; i++) {
        int nl = l + movimentos[i][0];
        int nc = c + movimentos[i][1];

        if (nl >= 0 && nl < m->linhas && nc >= 0 && nc < m->colunas) {
            char prox = m->mapa[nl][nc];
            if (!m->visitado[nl][nc] && podeMover(m->mapa[l][c], prox, i)) {
                int novo_dur = dur;
                if (pecas_restantes > 0) novo_dur -= m->Dp;
                movimentar(m, nl, nc, novo_dur, nivel+1, pecas_restantes);
                if (achou_destino) return;
            }
        }
    }

    m->visitado[l][c] = 0; // backtracking
}
