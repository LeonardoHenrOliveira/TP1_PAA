#ifndef NAVE_H
#define NAVE_H

#include "Mapa.h"

void movimentar(Mundo *m, int l, int c, int dur, int nivel);
int podeMover(char atual, char prox, int dir);

extern int chamadas_recursivas;
extern int max_nivel_recursao;
extern int achou_destino;


extern int x_inicio_global;
extern int y_inicio_global;
extern int voltando;

#endif
