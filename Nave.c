#include <stdio.h>
#include <stdlib.h>
#include "Mapa.h"
#include "Nave.h"

typedef struct {
    int l;
    int c;
    int dur;
    int pecas;
} Step;

int chamadas_recursivas = 0;
int max_nivel_recursao = 0;
int achou_destino = 0;

int movimentos[4][2] = { {-1,0}, {1,0}, {0,-1}, {0,1} };

static Step *current_steps = NULL;
static Step *final_steps = NULL;
static int final_len = 0;

int podeMover(char atual, char prox, int dir) {
    if (prox == '.' || prox == '\0') return 0;

    int eh_horizontal = (dir == 2 || dir == 3);
    int eh_vertical   = (dir == 0 || dir == 1);

    int saida_valida = 0;
    if (atual == '-' && eh_horizontal) saida_valida = 1;
    else if (atual == '|' && eh_vertical) saida_valida = 1;
    else if (atual == '+' || atual == 'P' || atual == 'F' || atual == 'X' || atual == 'B')
        saida_valida = 1;

    if (!saida_valida) return 0;

    int entrada_valida = 0;
    if (prox == '-') entrada_valida = eh_horizontal;
    else if (prox == '|') entrada_valida = eh_vertical;
    else if (prox == '+' || prox == 'P' || prox == 'F' || prox == 'X' || prox == 'B')
        entrada_valida = 1;

    return entrada_valida;
}

/**
 * Copia os passos atuais (nível 'nivel') para final_steps quando encontra solução
 */
void copiarCaminhoFinal(int nivel) {
    if (!final_steps || !current_steps) return;
    final_len = nivel;
    for (int i = 0; i < nivel; i++) {
        final_steps[i] = current_steps[i];
    }
}

/**
 * movimentar:
 *  - nivel: usado para indexar current_steps (nivel 1 -> index 0)
 *  - dur: durabilidade ao entrar nesta célula
 *  - pecas_restantes: número de peças que faltam ao entrar nesta célula
 */
void movimentar(Mundo *m, int l, int c, int dur, int nivel, int pecas_restantes) {
    chamadas_recursivas++;
    if (nivel > max_nivel_recursao) max_nivel_recursao = nivel;

    // registra passo atual na sequência
    if (current_steps) {
        current_steps[nivel-1].l = l;
        current_steps[nivel-1].c = c;
        current_steps[nivel-1].dur = dur;
        current_steps[nivel-1].pecas = pecas_restantes;
    }

    int coletada_antes = m->coletada[l][c];

    m->visitado[l][c] = 1;
    // mostra mapa se modo visual ativo
    mostrarMapa(m, l, c);

    if (m->mapa[l][c] == 'P' && m->coletada[l][c] == 0) {
        m->coletada[l][c] = 1;
        dur += m->A;
        pecas_restantes--;
        // atualiza o registro do passo, pois D e peças mudaram neste mesmo passo
        if (current_steps) {
            current_steps[nivel-1].dur = dur;
            current_steps[nivel-1].pecas = pecas_restantes;
        }
    }

    if (m->mapa[l][c] == 'F') {
        achou_destino = 1;
        copiarCaminhoFinal(nivel);
        return;
    }

    if (pecas_restantes == 0) {
        achou_destino = 1;
        copiarCaminhoFinal(nivel);
        return;
    }

    if (dur <= 0) {
        // restaura e volta
        m->visitado[l][c] = 0;
        m->coletada[l][c] = coletada_antes;
        return;
    }

    // tenta os 4 vizinhos
    for (int i = 0; i < 4; i++) {
        int nl = l + movimentos[i][0];
        int nc = c + movimentos[i][1];

        if (nl >= 0 && nl < m->linhas && nc >= 0 && nc < m->colunas) {
            char prox = m->mapa[nl][nc];

            if (!m->visitado[nl][nc] && podeMover(m->mapa[l][c], prox, i)) {
                int novo_dur = dur;

                if (prox == 'B') {
                    printf("Entrando em um setor perigoso! Dano extra!\n");
                    novo_dur -= m->Dp * 2; 
                } 
                else {
                    if (pecas_restantes > 0) novo_dur -= m->Dp;
                }

                movimentar(m, nl, nc, novo_dur, nivel+1, pecas_restantes);

                if (achou_destino) return; // corta demais explorações quando já encontrou solução
            }
        }
    }

    // backtracking: desfaz marcações no retorno
    m->visitado[l][c] = 0;
    m->coletada[l][c] = coletada_antes;
}

void iniciarJornada(Mundo *m, int inicioL, int inicioC) {
    chamadas_recursivas = 0;
    max_nivel_recursao = 0;
    achou_destino = 0;
    final_len = 0;

    int pecas_iniciais = 4;
    int max_steps = m->linhas * m->colunas;

    // aloca buffers para passos
    current_steps = malloc(sizeof(Step) * max_steps);
    final_steps   = malloc(sizeof(Step) * max_steps);
    if (!current_steps || !final_steps) {
        printf("Erro de alocação de memória para passos.\n");
        exit(1);
    }

    // inicia busca
    movimentar(m, inicioL, inicioC, m->D, 1, pecas_iniciais);

    // impressão do resultado final (apenas o caminho vencedor)
    if (achou_destino && final_len > 0) {
        for (int i = 0; i < final_len; i++) {
            printf("Linha: %d, Coluna: %d; D: %d, peças restantes: %d\n",
                   final_steps[i].l + 1,
                   final_steps[i].c + 1,
                   final_steps[i].dur,
                   final_steps[i].pecas);
        }
        // mensagem final condizente com o motivo da parada
        Step last = final_steps[final_len - 1];
        char ultima_char = m->mapa[last.l][last.c];
        if (ultima_char == 'F') {
            printf("\nA tripulação finalizou sua jornada.\n");
        } else if (last.pecas == 0) {
            printf("\nA jornada será finalizada sem mais desafios.\n");
        } else {
            // caso improvável: se achou_destino==1 mas não por F nem pecas==0
            printf("\nA tripulação finalizou sua jornada.\n");
        }
    } else {
        printf("\nApesar da bravura a tripulação falhou em sua jornada.\n");
    }

    // exibe modo de análise, se ativo
    if (MODO_ANALISE) {
        printf("\n===== MODO DE ANÁLISE =====\n");
        printf("Chamadas recursivas: %d\n", chamadas_recursivas);
        printf("Nível máximo de recursão: %d\n", max_nivel_recursao);
        printf("============================\n");
    }

    free(current_steps);
    free(final_steps);
    current_steps = final_steps = NULL;
    final_len = 0;
}