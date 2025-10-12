#ifndef NAVE_H
#define NAVE_H

#include "Mapa.h"

extern int chamadas_recursivas;
extern int max_nivel_recursao;
extern int achou_destino;

void movimentar(Mundo *m, int l, int c, int dur, int nivel);

#endif
