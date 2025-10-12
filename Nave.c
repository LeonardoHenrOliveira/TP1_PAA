#include <stdio.h>
#include "Nave.h"
#include "Mapa.h"

int chamadas_recursivas = 0;
int max_nivel_recursao = 0;
int achou_destino = 0;

int movimentos[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

// Verifica se pode mover
int podeMover(char atual, char prox, int dir) {
    if (prox == '.' || prox == '\0') return 0;
    if (prox == 'P' || prox == 'F' || prox == '+') return 1;
    if (prox == '-' && (dir == 2 || dir == 3)) return 1;
    if (prox == '|' && (dir == 0 || dir == 1)) return 1;
    return 0;
}

// Função recursiva principal
void movimentar(Mundo *m, int l, int c, int dur, int nivel) {
    chamadas_recursivas++;
    if (nivel > max_nivel_recursao) max_nivel_recursao = nivel;
    if (dur <= 0 || achou_destino) return;

    char atual = m->mapa[l][c];
    int pecas_restantes = contarPecasRestantes(m);

    mostrarMapa(m, l, c);
    printf("Linha: %d, Coluna: %d; D: %d, peças restantes: %d\n",
           l+1, c+1, dur, pecas_restantes);

    if (atual == 'F') {
        achou_destino = 1;
        if (pecas_restantes == 0)
            printf("\nA jornada será finalizada sem mais desafios.\n");
        else
            printf("\nA tripulação finalizou sua jornada.\n");
        return;
    }

    m->visitado[l][c] = 1;

    if (atual == 'P' && m->coletada[l][c] == 0) {
        m->coletada[l][c] = 1;
        dur += m->A;
        pecas_restantes = contarPecasRestantes(m);
    }

    for (int i = 0; i < 4; i++) {
        int nl = l + movimentos[i][0];
        int nc = c + movimentos[i][1];
        if (nl >= 0 && nl < m->linhas && nc >= 0 && nc < m->colunas) {
            char prox = m->mapa[nl][nc];
            if (!m->visitado[nl][nc] && podeMover(atual, prox, i)) {
                int novo_dur = dur;
                if (pecas_restantes > 0)
                    novo_dur -= m->Dp;
                movimentar(m, nl, nc, novo_dur, nivel + 1);
            }
        }
    }

    m->visitado[l][c] = 0;
}
