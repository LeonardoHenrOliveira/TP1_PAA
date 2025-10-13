#include <stdio.h>
#include "Mapa.h"
#include "Nave.h"

int chamadas_recursivas = 0;
int max_nivel_recursao = 0;
int achou_destino = 0;

int movimentos[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

int podeMover(char atual, char prox, int dir) {
    if (prox == '.' || prox == '\0') return 0;

    int eh_horizontal = (dir == 2 || dir == 3); // esquerda, direita
    int eh_vertical   = (dir == 0 || dir == 1); // cima, baixo

    int saida_valida = 0;
    if (atual == '-' && eh_horizontal) saida_valida = 1;
    else if (atual == '|' && eh_vertical) saida_valida = 1;
    else if (atual == '+' || atual == 'P' || atual == 'F' || atual == 'X')
        saida_valida = 1;

    if (!saida_valida) return 0;

    int entrada_valida = 0;
    if (prox == '-') entrada_valida = eh_horizontal;
    else if (prox == '|') entrada_valida = eh_vertical;
    else if (prox == '+' || prox == 'P' || prox == 'F')
        entrada_valida = 1;

    return entrada_valida;
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

    // 🚨 ENCERRAR SE ACABAR A ENERGIA
    if (dur <= 0) {
        printf("\nA nave ficou sem energia antes de concluir sua jornada.\n");
        achou_destino = 1; // impede mais chamadas recursivas
        return;
    }

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

// --- Função principal para iniciar o processo ---
void iniciarJornada(Mundo *m, int inicioL, int inicioC) {
    chamadas_recursivas = 0;
    max_nivel_recursao = 0;
    achou_destino = 0;

    int pecas_iniciais = 4; // sempre começa com 4 peças a coletar
    movimentar(m, inicioL, inicioC, m->D, 1, pecas_iniciais);

    if (!achou_destino) {
        printf("\nApesar da bravura, a tripulação falhou em sua jornada.\n");
    }

    printf("\nChamadas recursivas: %d\n", chamadas_recursivas);
    printf("Nível máximo de recursão: %d\n", max_nivel_recursao);
}
