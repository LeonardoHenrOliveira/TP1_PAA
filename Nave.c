#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Mapa.h"
#include "Nave.h"

int chamadas_recursivas = 0;
int max_nivel_recursao = 0;
int achou_destino = 0;

int movimentos[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} }; // cima, baixo, esquerda, direita

int podeMover(char atual, char prox, int dir) {
    if (prox == '.' || prox == '\0') return 0;

    int eh_horizontal = (dir == 2 || dir == 3);
    int eh_vertical   = (dir == 0 || dir == 1);

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

    // Salvar estado atual
    int coletada_antes = m->coletada[l][c];
    int dur_antes = dur;
    int pecas_antes = pecas_restantes;

    m->visitado[l][c] = 1;

    // Coleta peça se houver
    if (m->mapa[l][c] == 'P' && m->coletada[l][c] == 0) {
        m->coletada[l][c] = 1;
        dur += m->A;
        pecas_restantes--;
    }

    mostrarMapa(m, l, c);
    printf("Linha: %d, Coluna: %d; D: %d, peças restantes: %d\n",
           l+1, c+1, dur, pecas_restantes);

    // Condições de parada
    if (m->mapa[l][c] == 'F' || pecas_restantes == 0) {
        achou_destino = 1;
        if (pecas_restantes == 0)
            printf("\nA tripulação coletou todas as peças e finalizou a jornada!\n");
        else
            printf("\nA tripulação finalizou sua jornada no planeta das festividades!\n");

        m->visitado[l][c] = 0;
        m->coletada[l][c] = coletada_antes;
        return;
    }

    if (dur <= 0) {
        printf("\nA nave ficou sem energia neste caminho.\n");
        // Restaurar estado antes de voltar
        m->visitado[l][c] = 0;
        m->coletada[l][c] = coletada_antes;
        return;
    }

    // Tentar todos os vizinhos
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

    // Backtracking completo: restaurar visitados e coleta
    m->visitado[l][c] = 0;
    m->coletada[l][c] = coletada_antes;
    pecas_restantes = pecas_antes;
    dur = dur_antes;
}

// Função principal para iniciar a jornada
void iniciarJornada(Mundo *m, int inicioL, int inicioC) {
    chamadas_recursivas = 0;
    max_nivel_recursao = 0;
    achou_destino = 0;

    int pecas_iniciais = 4;

    // Cria backup da matriz de peças coletadas
    int **coletadas_backup = malloc(m->linhas * sizeof(int*));
    for (int i = 0; i < m->linhas; i++) {
        coletadas_backup[i] = malloc(m->colunas * sizeof(int));
    }

    while (!achou_destino) {
        // Copia estado atual das peças coletadas
        for (int i = 0; i < m->linhas; i++)
            for (int j = 0; j < m->colunas; j++)
                coletadas_backup[i][j] = m->coletada[i][j];

        printf("\n--- Recomeçando a jornada do ponto inicial ---\n");

        // Chama movimentar a partir do início
        movimentar(m, inicioL, inicioC, m->D, 1, pecas_iniciais);

        // Caso ele tenha falhado, restaura peças coletadas antes da tentativa
        if (!achou_destino) {
            for (int i = 0; i < m->linhas; i++)
                for (int j = 0; j < m->colunas; j++)
                    m->coletada[i][j] = coletadas_backup[i][j];

            break; // opcional: pode continuar tentando caminhos diferentes
        }
    }

    // Limpa backup
    for (int i = 0; i < m->linhas; i++) free(coletadas_backup[i]);
    free(coletadas_backup);

    printf("\nChamadas recursivas: %d\n", chamadas_recursivas);
    printf("Nível máximo de recursão: %d\n", max_nivel_recursao);
}
