#include "Leitura_Arquivo.h"

/* Cria um mapa vazio */
Mapa *mapa_criar() {
    Mapa *m = malloc(sizeof(Mapa));
    if (!m) return NULL;
    m->D = m->dec = m->A = 0;
    m->h = m->w = 0;
    m->grid = NULL;
    m->start_r = m->start_c = -1;
    m->total_p = 0;
    return m;
}

/* Libera memória do mapa */
void mapa_liberar(Mapa *m) {
    if (!m) return;
    if (m->grid) {
        for (int i = 0; i < m->h; ++i) free(m->grid[i]);
        free(m->grid);
    }
    free(m);
}

static int ler_linha_exata(FILE *f, char *buf, int w) {
    int read = 0;
    while (read < w) {
        int ch = fgetc(f);
        if (ch == EOF) return -1;
        if (ch == '\r' || ch == '\n') continue;
        buf[read++] = (char)ch;
    }

    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') break;
        if (ch == '\r') continue;
        ungetc(ch, f);
        break;
    }
    return 0;
}

Mapa *mapa_ler_de_arquivo(const char *nome_arquivo) {
    FILE *f = fopen(nome_arquivo, "r");
    if (!f) {
        return NULL;
    }

    Mapa *m = mapa_criar();
    if (!m) {
        fclose(f);
        return NULL;
    }

    // Ler primeira linha: D dec A
    if (fscanf(f, "%d %d %d", &m->D, &m->dec, &m->A) != 3) {
        mapa_liberar(m);
        fclose(f);
        return NULL;
    }

    // Ler altura e largura
    if (fscanf(f, "%d %d", &m->h, &m->w) != 2) {
        mapa_liberar(m);
        fclose(f);
        return NULL;
    }

    if (m->h <= 0 || m->w <= 0) {
        mapa_liberar(m);
        fclose(f);
        return NULL;
    }

    int ch;
    while ((ch = fgetc(f)) != EOF) {
        if (ch == '\n') break;
    }

    // Alocar grid
    m->grid = malloc(sizeof(char*) * m->h);
    if (!m->grid) {
        mapa_liberar(m);
        fclose(f);
        return NULL;
    }
    for (int i = 0; i < m->h; ++i) {
        m->grid[i] = malloc(sizeof(char) * (m->w + 1)); // +1 para '\0' se quisermos
        if (!m->grid[i]) {
            // liberar alocado
            for (int k = 0; k < i; ++k) free(m->grid[k]);
            free(m->grid);
            mapa_liberar(m);
            fclose(f);
            return NULL;
        }
        m->grid[i][m->w] = '\0';
    }

    m->total_p = 0;
    m->start_r = m->start_c = -1;

    for (int i = 0; i < m->h; ++i) {
        if (ler_linha_exata(f, m->grid[i], m->w) != 0) {
            mapa_liberar(m);
            fclose(f);
            return NULL;
        }
        // processar a linha para contar P e achar X
        for (int j = 0; j < m->w; ++j) {
            char c = m->grid[i][j];
            if (c == 'P') m->total_p++;
            else if (c == 'X') {
                if (m->start_r == -1) {
                    m->start_r = i;
                    m->start_c = j;
                }
            }
        }
    }

    fclose(f);
    return m;
}

void mapa_imprimir_relatorio(const Mapa *m) {
    if (!m) return;
    printf("D = %d, D' = %d, A = %d\n", m->D, m->dec, m->A);
    printf("Altura = %d, Largura = %d\n", m->h, m->w);
    printf("Mapa lido:\n");
    for (int i = 0; i < m->h; ++i) {
        printf("%s\n", m->grid[i]);
    }
    if (m->start_r >= 0)
        printf("Posicao inicial X: linha %d, coluna %d (base 1).\n", m->start_r + 1, m->start_c + 1);
    else
        printf("Posicao inicial X: NAO encontrada no mapa.\n");
    printf("Total de pecas P no mapa: %d\n", m->total_p);
}