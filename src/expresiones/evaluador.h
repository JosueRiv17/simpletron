#ifndef EVALUADOR_H
#define EVALUADOR_H
#define PROFUNDIDAD_MAXIMA 10

#include <stdbool.h>

bool validarParentesis(const char *expresion, int *profundidadMaxima);

void infijaAPostfija(const char *infija, char *postfija);

bool evaluarPostfija(const char *postfija, double *resultado);
bool validarSintaxis(const char *expresion);

#endif
