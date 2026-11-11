#include <stdio.h>
#include "evaluador.h"

int main() {
    int profundidad;
    char postfija[100];
    double resultado;

    char expresion[] = "5+";

   if (!validarParentesis(expresion, &profundidad) ||
    !validarSintaxis(expresion)) {

    printf("Expresion invalida.\n");
    return 1;
}

    printf("Expresion valida. Profundidad: %d\n", profundidad);

    infijaAPostfija(expresion, postfija);

    printf("Postfija: %s\n", postfija);

    if (evaluarPostfija(postfija, &resultado)) {
        printf("Resultado: %.2f\n", resultado);
    } else {
        printf("Error al evaluar expresion.\n");
    }

    return 0;
}
