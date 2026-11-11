#include "evaluador.h"
#include <stdlib.h>
#include <math.h>
#include <string.h>
bool validarParentesis(const char *expresion, int *profundidadMaxima) {
    int profundidad = 0;
    int maxima = 0;
    int i;

    for (i = 0; expresion[i] != '\0'; i++) {

        if (expresion[i] == '(') {
            profundidad++;

           if (profundidad > maxima) {
			    maxima = profundidad;
			}

		if (profundidad > PROFUNDIDAD_MAXIMA) {
		    *profundidadMaxima = maxima;
		    return false;
		}
        }
        else if (expresion[i] == ')') {
            profundidad--;

            if (profundidad < 0) {
                *profundidadMaxima = maxima;
                return false;
            }
        }
    }

    *profundidadMaxima = maxima;

    return profundidad == 0;
}
int precedencia(char operador) {
    switch (operador) {
        case '+':
        case '-':
            return 1;

        case '*':
        case '/':
            return 2;

        case '^':
            return 3;

        default:
            return 0;
    }
}
void infijaAPostfija(const char *infija, char *postfija) {
    char pila[100];
    int tope = -1;
    int j = 0;
    int i = 0;

    while (infija[i] != '\0') {

        if (infija[i] == ' ') {
            i++;
            continue;
        }

        /* Leer numeros completos */
        if (infija[i] >= '0' && infija[i] <= '9') {

            while (infija[i] >= '0' && infija[i] <= '9') {
                postfija[j++] = infija[i++];
            }

            postfija[j++] = ' ';
        }

        /* Leer variables */
        else if (infija[i] >= 'a' && infija[i] <= 'z') {
            postfija[j++] = infija[i++];
            postfija[j++] = ' ';
        }

        /* Abrir parentesis */
        else if (infija[i] == '(') {
            pila[++tope] = infija[i++];
        }

        /* Cerrar parentesis */
        else if (infija[i] == ')') {

            while (tope >= 0 && pila[tope] != '(') {
                postfija[j++] = pila[tope--];
                postfija[j++] = ' ';
            }

            if (tope >= 0) {
                tope--;
            }

            i++;
        }

        /* Operadores */
        else {
            char actual = infija[i];

            while (tope >= 0 && pila[tope] != '(' &&
                   (precedencia(pila[tope]) > precedencia(actual) ||
                   (precedencia(pila[tope]) == precedencia(actual) &&
                    actual != '^'))) {

                postfija[j++] = pila[tope--];
                postfija[j++] = ' ';
            }

            pila[++tope] = actual;
            i++;
        }
    }

    /* Vaciar pila */
    while (tope >= 0) {
        postfija[j++] = pila[tope--];
        postfija[j++] = ' ';
    }

    postfija[j] = '\0';
}

bool evaluarPostfija(const char *postfija, double *resultado) {
    double pila[100];
    int tope = -1;
    int i = 0;

    while (postfija[i] != '\0') {

        if (postfija[i] == ' ') {
            i++;
            continue;
        }

        /* Leer numero completo */
        if ((postfija[i] >= '0' && postfija[i] <= '9') ||
            postfija[i] == '.') {

            char numero[50];
            int j = 0;

            while ((postfija[i] >= '0' && postfija[i] <= '9') ||
                   postfija[i] == '.') {

                if (j >= 49) return false;

                numero[j++] = postfija[i++];
            }

            numero[j] = '\0';

            pila[++tope] = atof(numero);
        }

        /* Procesar operadores */
        else {
            double b, a;

            if (tope < 1) return false;

            b = pila[tope--];
            a = pila[tope--];

            switch (postfija[i]) {
                case '+': pila[++tope] = a + b; break;
                case '-': pila[++tope] = a - b; break;
                case '*': pila[++tope] = a * b; break;

                case '/':
                    if (b == 0) return false;
                    pila[++tope] = a / b;
                    break;

                case '^':
                    pila[++tope] = pow(a, b);
                    break;

                default:
                    return false;
            }

            i++;
        }
    }

    if (tope != 0) return false;

    *resultado = pila[tope];

    return true;
}
bool validarSintaxis(const char *expresion) {
    int i = 0;
    int esperaNumero = 1;
    int parentesis = 0;

    while (expresion[i] != '\0') {

        if (expresion[i] == ' ') {
            i++;
            continue;
        }

        if ((expresion[i] >= '0' && expresion[i] <= '9') ||
            (expresion[i] >= 'a' && expresion[i] <= 'z')) {

            if (!esperaNumero) return false;

            while ((expresion[i] >= '0' && expresion[i] <= '9') ||
                   (expresion[i] >= 'a' && expresion[i] <= 'z')) {
                i++;
            }

            esperaNumero = 0;
        }
        else if (expresion[i] == '(') {
            if (!esperaNumero) return false;

            parentesis++;
            i++;
        }
        else if (expresion[i] == ')') {
            if (esperaNumero || parentesis == 0) return false;

            parentesis--;
            i++;
            esperaNumero = 0;
        }
        else if (expresion[i] == '+' || expresion[i] == '-' ||
                 expresion[i] == '*' || expresion[i] == '/' ||
                 expresion[i] == '^') {

            if (esperaNumero) return false;

            esperaNumero = 1;
            i++;
        }
        else {
            return false;
        }
    }

    return !esperaNumero && parentesis == 0;
}
