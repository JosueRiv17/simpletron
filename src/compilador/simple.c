#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "evaluador.h"

#define MAX_LINEAS 100
#define MAX_TAMANO 200
#define MAX_INSTRUCCIONES 1000
#define MAX_CONSTANTES 100
#define MAX_TEMPORALES 100

int direccionesTemporales[MAX_TEMPORALES];
int cantidadTemporales = 0;
int direccionInicioTemporales = 0;

int constantes[MAX_CONSTANTES];
int posicionesConstantes[MAX_CONSTANTES];
int cantidadConstantes = 0;

int codigoSML[MAX_INSTRUCCIONES];
int cantidadSML = 0;

typedef struct {
    int numero;
    char instruccion[MAX_TAMANO];
} LineaSimple;
typedef struct {
    int numeroSimple;
    int direccionSML;
    int cantidadInstrucciones;
} TablaLineas;

LineaSimple programa[MAX_LINEAS];
int cantidadLineas = 0;

double valoresVariables[26];
int variablesUsadas[26] = {0};

int posicionesVariables[26];
int cantidadVariables = 0;
TablaLineas tablaLineas[MAX_LINEAS];
int cantidadInstruccionesSML = 0;


int cargarPrograma(const char *archivo) {
    FILE *fp;
    char linea[MAX_TAMANO];

    fp = fopen(archivo, "r");

    if (fp == NULL) {
        printf("Error al abrir el archivo.\n");
        return 0;
    }

    while (fgets(linea, sizeof(linea), fp) != NULL) {

        if (cantidadLineas >= MAX_LINEAS) {
            printf("Limite de lineas alcanzado.\n");
            fclose(fp);
            return 0;
        }

        if (sscanf(linea, "%d %[^\n]",
                   &programa[cantidadLineas].numero,
                   programa[cantidadLineas].instruccion) == 2) {

            cantidadLineas++;
        }
    }

    fclose(fp);
    return 1;
}
int validarLineas() {
    int i;

    for (i = 0; i < cantidadLineas; i++) {

        if (programa[i].numero <= 0) {
            printf("Error: numero de linea invalido.\n");
            return 0;
        }

        if (i > 0 &&
            programa[i].numero <= programa[i - 1].numero) {

            printf("Error: las lineas deben estar en orden ascendente.\n");
            return 0;
        }
    }

    return 1;
}
int validarComandos() {
    int i;
    char comando[20];

    for (i = 0; i < cantidadLineas; i++) {

        if (sscanf(programa[i].instruccion, "%19s", comando) != 1) {
            printf("Error: instruccion vacia en linea %d.\n",
                   programa[i].numero);
            return 0;
        }

        if (strcmp(comando, "rem") != 0 &&
            strcmp(comando, "input") != 0 &&
            strcmp(comando, "let") != 0 &&
            strcmp(comando, "print") != 0 &&
            strcmp(comando, "goto") != 0 &&
            strcmp(comando, "if") != 0 &&
            strcmp(comando, "end") != 0) {

            printf("Error: comando desconocido '%s' en linea %d.\n",
                   comando, programa[i].numero);
            return 0;
        }
    }

    return 1;
}
int validarInstrucciones() {
    int i;
    char comando[20];
    char argumento[100];

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        if (strcmp(comando, "rem") == 0 ||
            strcmp(comando, "end") == 0) {
            continue;
        }

        if (sscanf(programa[i].instruccion, "%19s %99s",
                   comando, argumento) != 2) {

            printf("Error: falta un argumento en linea %d.\n",
                   programa[i].numero);
            return 0;
        }

    }

    return 1;
}
int validarVariable(char variable) {
    return variable >= 'a' && variable <= 'z';
}
void registrarVariable(char variable) {
    int posicion;

    posicion = variable - 'a';

    if (posicion >= 0 && posicion < 26) {
        variablesUsadas[posicion] = 1;
    }
}



int validarVariables() {
    int i;
    char comando[20];
    char variable;
    char operador[3];
    char valor[30];
    char gotoTexto[20];
    int destino;
    int asignadas[26] = {0};
    char *expresion;
    char *p;

    for (i = 0; i < cantidadLineas; i++) {

        if (sscanf(programa[i].instruccion,
                   "%19s", comando) != 1) {
            continue;
        }

        /* INPUT */
        if (strcmp(comando, "input") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %c", &variable) != 1 ||
                !validarVariable(variable)) {
                printf("Error: variable invalida en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            asignadas[variable - 'a'] = 1;
        }

        /* LET */
        else if (strcmp(comando, "let") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %c", &variable) != 1 ||
                !validarVariable(variable)) {
                printf("Error: variable invalida en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            expresion = strchr(programa[i].instruccion, '=');

            if (expresion == NULL) {
                printf("Error: expresion invalida en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            expresion++;

            for (p = expresion; *p != '\0'; p++) {

                if (*p >= 'a' && *p <= 'z') {

                    if (!asignadas[*p - 'a']) {
                        printf("Error: variable '%c' no inicializada en linea %d.\n",
                               *p, programa[i].numero);
                        return 0;
                    }
                }
            }

            asignadas[variable - 'a'] = 1;
        }

        /* IF */
        else if (strcmp(comando, "if") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %c %2s %29s %19s %d",
                       &variable, operador, valor,
                       gotoTexto, &destino) != 5) {
                printf("Error: IF invalido en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            if (!validarVariable(variable)) {
                printf("Error: variable invalida en IF.\n");
                return 0;
            }

            if (!asignadas[variable - 'a']) {
                printf("Error: variable '%c' no inicializada en linea %d.\n",
                       variable, programa[i].numero);
                return 0;
            }
        }

        /* PRINT */
        else if (strcmp(comando, "print") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %c", &variable) != 1 ||
                !validarVariable(variable)) {
                printf("Error: variable invalida en PRINT.\n");
                return 0;
            }

            if (!asignadas[variable - 'a']) {
                printf("Error: variable '%c' no inicializada en linea %d.\n",
                       variable, programa[i].numero);
                return 0;
            }
        }
    }

    return 1;
}




void registrarVariables() {
    int i;
    char comando[20];
    char variable;
    char valor[30];
    char *expresion;
    int j;

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        /* INPUT */
        if (strcmp(comando, "input") == 0) {
            sscanf(programa[i].instruccion,
                   "%*s %c", &variable);

            registrarVariable(variable);
        }

        /* LET */
        else if (strcmp(comando, "let") == 0) {
            sscanf(programa[i].instruccion,
                   "%*s %c", &variable);

            registrarVariable(variable);

            expresion = strchr(programa[i].instruccion, '=');

            if (expresion != NULL) {
                expresion++;

                for (j = 0; expresion[j] != '\0'; j++) {
                    if (expresion[j] >= 'a' &&
                        expresion[j] <= 'z') {
                        registrarVariable(expresion[j]);
                    }
                }
            }
        }

        /* PRINT */
        else if (strcmp(comando, "print") == 0) {
            sscanf(programa[i].instruccion,
                   "%*s %c", &variable);

            registrarVariable(variable);
        }

        /* IF */
        else if (strcmp(comando, "if") == 0) {
            if (sscanf(programa[i].instruccion,
                       "%*s %c %*s %29s",
                       &variable, valor) == 2) {

                registrarVariable(variable);

                if (valor[0] >= 'a' && valor[0] <= 'z' &&
                    valor[1] == '\0') {
                    registrarVariable(valor[0]);
                }
            }
        }
    }
}


void asignarPosicionesVariables() {
    int i;
    int siguienteDireccion;

    cantidadVariables = 0;

    /* Las variables empiezan despues del codigo SML */
    siguienteDireccion = cantidadInstruccionesSML;

    for (i = 0; i < 26; i++) {
        posicionesVariables[i] = -1;

        if (variablesUsadas[i]) {
            posicionesVariables[i] = siguienteDireccion;
            siguienteDireccion++;
            cantidadVariables++;
        }
    }
}


void asignarPosicionesConstantes() {
    int i;
    int siguienteDireccion;

    /* Las constantes empiezan despues de las variables */
    siguienteDireccion = cantidadInstruccionesSML + cantidadVariables;

    for (i = 0; i < cantidadConstantes; i++) {
        posicionesConstantes[i] = siguienteDireccion;
        siguienteDireccion++;
    }
}

int buscarDireccionConstante(int valor) {
    int i;

    for (i = 0; i < cantidadConstantes; i++) {
        if (constantes[i] == valor) {
            return posicionesConstantes[i];
        }
    }

    return -1;
}

int buscarDireccionVariable(char variable) {
    int posicion;

    posicion = variable - 'a';

    if (posicion >= 0 && posicion < 26 &&
        variablesUsadas[posicion]) {
        return posicionesVariables[posicion];
    }

    return -1;
}

int esNumero(const char *token) {
    int i;

    if (token[0] == '\0') {
        return 0;
    }

    for (i = 0; token[i] != '\0'; i++) {
        if (token[i] < '0' || token[i] > '9') {
            return 0;
        }
    }

    return 1;
}
int generarExpresionPostfija(const char *postfija, int direccionDestino) {
    char copia[MAX_TAMANO];
    char *token;

    int pila[MAX_TEMPORALES];
    int tope = -1;

    int direccion;
    int izquierda;
    int derecha;
    int operador;

    strcpy(copia, postfija);

    token = strtok(copia, " ");

    while (token != NULL) {

        /* Primero identificamos los operadores */
        if (strlen(token) == 1 &&
            (token[0] == '+' ||
             token[0] == '-' ||
             token[0] == '*' ||
             token[0] == '/' ||
             token[0] == '^')) {

            if (tope < 1) {
                return 0;
            }

            derecha = pila[tope];
            tope--;

            izquierda = pila[tope];
            tope--;

            switch (token[0]) {
                case '+': operador = 30; break;
                case '-': operador = 31; break;
                case '/': operador = 32; break;
                case '*': operador = 33; break;
                case '^': operador = 35; break;
                default: return 0;
            }

            agregarInstruccion(20000 + izquierda);
            agregarInstruccion(operador * 1000 + derecha);
            agregarInstruccion(21000 + izquierda);

            tope++;
            pila[tope] = izquierda;
        }

        /* Después identificamos los operandos */
        else {

            if (tope + 1 >= cantidadTemporales) {
                return 0;
            }

            if (esNumero(token)) {
                direccion = buscarDireccionConstante(atoi(token));
            }
            else if (strlen(token) == 1 &&
                     token[0] >= 'a' && token[0] <= 'z') {
                direccion = buscarDireccionVariable(token[0]);
            }
            else {
                return 0;
            }

            if (direccion == -1) {
                return 0;
            }

            tope++;
            pila[tope] = direccionesTemporales[tope];

            agregarInstruccion(20000 + direccion);
            agregarInstruccion(21000 + pila[tope]);
        }

        token = strtok(NULL, " ");
    }

    if (tope != 0) {
        return 0;
    }

    agregarInstruccion(20000 + pila[0]);
    agregarInstruccion(21000 + direccionDestino);

    return 1;
}

int calcularMaximoTemporales() {
    int i;
    int profundidad;
    int maximo;
    char variable;
    char expresion[MAX_TAMANO];
    char postfija[MAX_TAMANO];
    char copia[MAX_TAMANO];
    char *token;

    maximo = 0;

    for (i = 0; i < cantidadLineas; i++) {

        if (strncmp(programa[i].instruccion, "let ", 4) == 0) {

            sscanf(programa[i].instruccion,
                   "let %c = %199[^\n]",
                   &variable, expresion);

            infijaAPostfija(expresion, postfija);

            strcpy(copia, postfija);
            token = strtok(copia, " ");

            profundidad = 0;

            while (token != NULL) {

                if (strlen(token) == 1 &&
                    (token[0] == '+' || token[0] == '-' ||
                     token[0] == '*' || token[0] == '/' ||
                     token[0] == '^')) {

                    profundidad--;

                } else {

                    profundidad++;

                    if (profundidad > maximo) {
                        maximo = profundidad;
                    }
                }

                token = strtok(NULL, " ");
            }
        }
    }

    return maximo;
}

void asignarPosicionesTemporales() {
    int i;

    direccionInicioTemporales =
        cantidadInstruccionesSML +
        cantidadVariables +
        cantidadConstantes;

    for (i = 0; i < MAX_TEMPORALES; i++) {
        direccionesTemporales[i] = -1;
    }

    cantidadTemporales = calcularMaximoTemporales();

    for (i = 0; i < cantidadTemporales; i++) {
        direccionesTemporales[i] =
            direccionInicioTemporales + i;
    }
}

int contarInstrucciones(int indice) {
    char comando[20];
    char expresion[300];
    char postfija[300];
    char copia[300];
    char operador[3];
    char *token;
    int destino;
    int cantidad = 0;

    sscanf(programa[indice].instruccion, "%19s", comando);

    if (strcmp(comando, "rem") == 0) {
        return 0;
    }

    if (strncmp(programa[indice].instruccion, "input", 5) == 0 ||
    strncmp(programa[indice].instruccion, "print", 5) == 0) {
    return 1;
}

    if (strcmp(comando, "goto") == 0 ||
        strcmp(comando, "end") == 0) {
        return 1;
    }

    
if (strcmp(comando, "let") == 0) {
    int operandos = 0;
    int operadores = 0;

    sscanf(programa[indice].instruccion,
           "%*s %*s %*s %299[^\n]", expresion);

    infijaAPostfija(expresion, postfija);

    strcpy(copia, postfija);
    token = strtok(copia, " ");

    while (token != NULL) {

        if (strlen(token) == 1 &&
            (token[0] == '+' ||
             token[0] == '-' ||
             token[0] == '*' ||
             token[0] == '/' ||
             token[0] == '^')) {

            operadores++;
        } else {
            operandos++;
        }

        token = strtok(NULL, " ");
    }

    cantidad = (operandos * 2) + (operadores * 3) + 2;

    return cantidad;
}


    
if (strcmp(comando, "if") == 0) {

    sscanf(programa[indice].instruccion,
           "%*s %*c %2s %*s %*s %d",
           operador, &destino);

    if (strcmp(operador, "<") == 0 ||
        strcmp(operador, ">") == 0 ||
        strcmp(operador, "==") == 0) {
        return 3;
    }

    return 4;
}


    return 0;
}

void primeraPasada() {
    int i;

    cantidadInstruccionesSML = 0;

    for (i = 0; i < cantidadLineas; i++) {

        tablaLineas[i].numeroSimple = programa[i].numero;

        tablaLineas[i].direccionSML =
            cantidadInstruccionesSML;

        tablaLineas[i].cantidadInstrucciones =
            contarInstrucciones(i);

        cantidadInstruccionesSML +=
            tablaLineas[i].cantidadInstrucciones;
    }
}

int buscarDireccionSML(int numeroLinea) {
    int i;

    for (i = 0; i < cantidadLineas; i++) {

        if (tablaLineas[i].numeroSimple == numeroLinea) {
            return tablaLineas[i].direccionSML;
        }
    }

    return -1;
}

void agregarInstruccion(int instruccion) {
	
	
    if (cantidadSML < MAX_INSTRUCCIONES) {
        codigoSML[cantidadSML] = instruccion;
        cantidadSML++;
        
    } else {
        printf("Error: memoria SML llena.\n");
    }
}

int obtenerDireccionOperando(char *operando) {
    int posicion;

    if (operando[0] >= 'a' && operando[0] <= 'z' &&
        operando[1] == '\0') {

        posicion = operando[0] - 'a';
        return posicionesVariables[posicion];
    }

    return -1;
}

void registrarConstante(int numero) {
    int i;

    /* Evitar constantes duplicadas */
    for (i = 0; i < cantidadConstantes; i++) {
        if (constantes[i] == numero) {
            return;
        }
    }

    if (cantidadConstantes < MAX_CONSTANTES) {
        constantes[cantidadConstantes] = numero;
        posicionesConstantes[cantidadConstantes] = -1;
        cantidadConstantes++;
    }
}

void registrarConstantes() {
    int i;
    char comando[20];
    char expresion[300];
    char postfija[300];
    char copia[300];
    char *token;
    char *fin;
    long numero;

    cantidadConstantes = 0;

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        if (strcmp(comando, "let") == 0) {

            sscanf(programa[i].instruccion,
                   "%*s %*s %*s %299[^\n]", expresion);

            infijaAPostfija(expresion, postfija);

            strcpy(copia, postfija);
            token = strtok(copia, " ");

            while (token != NULL) {

                numero = strtol(token, &fin, 10);

                if (*token != '\0' && *fin == '\0') {
                    registrarConstante((int)numero);
                }

                token = strtok(NULL, " ");
            }
        }
                if (strcmp(comando, "if") == 0) {

            int valorDerecha;
            char variable;
            char operador[3];
            int destino;

            sscanf(programa[i].instruccion,
                   "%*s %c %2s %d %*s %d",
                   &variable,
                   operador,
                   &valorDerecha,
                   &destino);

            registrarConstante(valorDerecha);
        }
    }
}

void generarCodigo() {
    int i;
    int posicion;
    int direccion;
    char comando[20];
    char variable;
        char operador[3];
    int valorDerecha;
    int direccionDerecha;
    int destinoSimple;

    cantidadSML = 0;

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        /* INPUT */
        if (strcmp(comando, "input") == 0) {

            sscanf(programa[i].instruccion,
                   "%*s %c", &variable);

            posicion = variable - 'a';

            agregarInstruccion(10000 + posicionesVariables[posicion]);
        }

        /* PRINT */
        else if (strcmp(comando, "print") == 0) {

            sscanf(programa[i].instruccion,
                   "%*s %c", &variable);

            posicion = variable - 'a';

           agregarInstruccion(11000 + posicionesVariables[posicion]);
        }

        /* GOTO */
        else if (strcmp(comando, "goto") == 0) {

            sscanf(programa[i].instruccion,
                   "%*s %d", &direccion);

            direccion = buscarDireccionSML(direccion);

            agregarInstruccion(40000 + direccion);
        }else if (strcmp(comando, "let") == 0) {
    char variable;
    char expresion[MAX_TAMANO];
    char postfija[MAX_TAMANO];
    int direccionDestino;

    sscanf(programa[i].instruccion,
           "let %c = %199[^\n]",
           &variable,
           expresion);

    infijaAPostfija(expresion, postfija);

    direccionDestino = buscarDireccionVariable(variable);

    if (direccionDestino == -1) {
        printf("Error: variable destino no encontrada.\n");
        return;
    }

    if (!generarExpresionPostfija(postfija, direccionDestino)) {
        printf("Error al generar expresion SML.\n");
        return;
    }
}
        
/* IF */
else if (strcmp(comando, "if") == 0) {

    sscanf(programa[i].instruccion,
           "%*s %c %2s %d %*s %d",
           &variable, operador, &valorDerecha, &destinoSimple);

    posicion = variable - 'a';
    direccion = posicionesVariables[posicion];
    direccionDerecha = buscarDireccionConstante(valorDerecha);
    destinoSimple = buscarDireccionSML(destinoSimple);

    /* MENOR QUE */
    if (strcmp(operador, "<") == 0) {
        agregarInstruccion(20000 + direccion);
        agregarInstruccion(31000 + direccionDerecha);
        agregarInstruccion(41000 + destinoSimple);
    }

    /* MENOR O IGUAL */
    else if (strcmp(operador, "<=") == 0) {
        agregarInstruccion(20000 + direccion);
        agregarInstruccion(31000 + direccionDerecha);
        agregarInstruccion(41000 + destinoSimple);
        agregarInstruccion(42000 + destinoSimple);
    }

    /* MAYOR QUE */
    else if (strcmp(operador, ">") == 0) {
        agregarInstruccion(20000 + direccionDerecha);
        agregarInstruccion(31000 + direccion);
        agregarInstruccion(41000 + destinoSimple);
    }

    /* MAYOR O IGUAL */
    else if (strcmp(operador, ">=") == 0) {
        agregarInstruccion(20000 + direccionDerecha);
        agregarInstruccion(31000 + direccion);
        agregarInstruccion(41000 + destinoSimple);
        agregarInstruccion(42000 + destinoSimple);
    }

    /* IGUAL */
    else if (strcmp(operador, "==") == 0) {
        agregarInstruccion(20000 + direccion);
        agregarInstruccion(31000 + direccionDerecha);
        agregarInstruccion(42000 + destinoSimple);
    }

    /* DIFERENTE */
    else if (strcmp(operador, "!=") == 0) {
        agregarInstruccion(20000 + direccion);
        agregarInstruccion(31000 + direccionDerecha);

        agregarInstruccion(
            42000 +
            (tablaLineas[i].direccionSML +
             tablaLineas[i].cantidadInstrucciones)
        );

        agregarInstruccion(40000 + destinoSimple);
    }

    else {
        printf("Error: operador IF no implementado.\n");
        return;
    }
}

        /* END */
        else if (strcmp(comando, "end") == 0) {

            agregarInstruccion(99000);
        }
    }
}

void generarArchivoSML() {
    FILE *archivo;
    int i;

    archivo = fopen("programa.simp", "w");

    if (archivo == NULL) {
        printf("ERROR: No se pudo crear programa.simp\n");
        return;
    }

    /* Escribir instrucciones */
    for (i = 0; i < cantidadSML; i++) {
        fprintf(archivo, "%d\n", codigoSML[i]);
    }

    /* Inicializar variables en cero */
    for (i = 0; i < 26; i++) {
        if (variablesUsadas[i]) {
            fprintf(archivo, "0\n");
        }
    }

    /* Escribir valores de constantes */
    for (i = 0; i < cantidadConstantes; i++) {
        fprintf(archivo, "%d\n", constantes[i]);
    }

    /* Inicializar temporales en cero */
    for (i = 0; i < cantidadTemporales; i++) {
        fprintf(archivo, "0\n");
    }

    fclose(archivo);

    printf("\nArchivo programa.simp generado correctamente.\n");
}

int validarLet() {
    int i;
    char comando[20];
    char variable;
    char igual;

    for (i = 0; i < cantidadLineas; i++) {

        if (sscanf(programa[i].instruccion, "%19s", comando) != 1)
            continue;

        if (strcmp(comando, "let") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %c %c",
                       &variable, &igual) != 2 ||
                igual != '=') {

                printf("Error: estructura LET invalida en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            if (!validarVariable(variable)) {
                printf("Error: variable invalida en LET, linea %d.\n",
                       programa[i].numero);
                return 0;
            }
        }
    }

    return 1;
}
int validarExpresiones() {
    int i;
    char comando[20];
    char expresion[150];
    int profundidad;

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        if (strcmp(comando, "let") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %*s %*s %149[^\n]",
                       expresion) != 1) {

                printf("Error: expresion faltante en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            if (!validarParentesis(expresion, &profundidad) ||
                !validarSintaxis(expresion)) {

                printf("Error: expresion invalida en linea %d.\n",
                       programa[i].numero);
                return 0;
            }
        }
    }

    return 1;
}
int validarGoto() {
    int i;
    int destino;
    char comando[20];

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        if (strcmp(comando, "goto") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %d", &destino) != 1) {

                printf("Error: destino GOTO invalido en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            if (destino <= 0) {
                printf("Error: numero de destino invalido.\n");
                return 0;
            }
            if (!existeLinea(destino)) {
    printf("Error: la linea destino %d no existe.\n", destino);
    return 0;
}
        }
    }

    return 1;
}
int existeLinea(int numero) {
    int i;

    for (i = 0; i < cantidadLineas; i++) {
        if (programa[i].numero == numero) {
            return 1;
        }
    }

    return 0;
}
int validarIf() {
    int i;
    int destino;
    char comando[20];
    char variable;
    char operador[3];
    char gotoTexto[20];
    char valor[30];

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        if (strcmp(comando, "if") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%*s %c %2s %29s %19s %d",
                       &variable, operador, valor,
                       gotoTexto, &destino) != 5) {

                printf("Error: estructura IF invalida en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            if (!validarVariable(variable)) {
                printf("Error: variable invalida en IF.\n");
                return 0;
            }

            if (strcmp(operador, "<") != 0 &&
                strcmp(operador, "<=") != 0 &&
                strcmp(operador, ">") != 0 &&
                strcmp(operador, ">=") != 0 &&
                strcmp(operador, "==") != 0 &&
                strcmp(operador, "!=") != 0) {

                printf("Error: operador de comparacion invalido.\n");
                return 0;
            }

            if (strcmp(gotoTexto, "goto") != 0) {
                printf("Error: IF debe contener GOTO.\n");
                return 0;
            }

            if (!existeLinea(destino)) {
                printf("Error: destino IF inexistente.\n");
                return 0;
            }
        }
    }

    return 1;
}
int validarOtrosComandos() {
    int i;
    char comando[20];
    char argumento[100];
    char extra[100];

    for (i = 0; i < cantidadLineas; i++) {

        sscanf(programa[i].instruccion, "%19s", comando);

        if (strcmp(comando, "input") == 0 ||
            strcmp(comando, "print") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%19s %99s %99s",
                       comando, argumento, extra) != 2) {

                printf("Error: instruccion invalida en linea %d.\n",
                       programa[i].numero);
                return 0;
            }

            if (strcmp(comando, "input") == 0 &&
                !validarVariable(argumento[0])) {

                printf("Error: INPUT requiere una variable.\n");
                return 0;
            }
        }

        if (strcmp(comando, "end") == 0) {

            if (sscanf(programa[i].instruccion,
                       "%19s %99s", comando, argumento) != 1) {

                printf("Error: END no debe tener argumentos.\n");
                return 0;
            }
        }
    }

    return 1;
}
int main() {
int i;
    if (!cargarPrograma("programa.simple")) {
        return 1;
    }
    printf("\nDEBUG: Cantidad de lineas cargadas: %d\n",
       cantidadLineas);

for (i = 0; i < cantidadLineas; i++) {
    printf("DEBUG: %d %s\n",
           programa[i].numero,
           programa[i].instruccion);
}
    if (!validarLineas()) {
    return 1;
}
if (!validarComandos()) {
    return 1;
}
if (!validarInstrucciones()) {
    return 1;
}
if (!validarVariables()) {
    return 1;
}
if (!validarLet()) {
    return 1;
}
if (!validarExpresiones()) {
    return 1;
}
if (!validarGoto()) {
    return 1;
}
if (!validarIf()) {
    return 1;
}
if (!validarOtrosComandos()) {
    return 1;
}
registrarVariables();
registrarConstantes();

printf("\nConstantes utilizadas:\n");

for (i = 0; i < cantidadConstantes; i++) {
    printf("Constante: %d\n", constantes[i]);
}
printf("\nVariables utilizadas:\n");

for (i = 0; i < 26; i++) {
    if (variablesUsadas[i]) {
        printf("%c\n", 'a' + i);
    }
}

primeraPasada();
asignarPosicionesVariables();
asignarPosicionesConstantes();
asignarPosicionesTemporales();
generarCodigo();
generarArchivoSML();
printf("\nCodigo SML generado:\n");
printf("-------------------------\n");

for (i = 0; i < cantidadSML; i++) {
    printf("%d: %05d\n", i, codigoSML[i]);
}

printf("-------------------------\n");
printf("\nPrueba de conversion de direcciones:\n");

printf("Linea 50 -> Direccion SML: %d\n",
       buscarDireccionSML(50));

printf("Linea 30 -> Direccion SML: %d\n",
       buscarDireccionSML(30));
printf("\nPrimera pasada del compilador:\n");
printf("-----------------------------------\n");

for (i = 0; i < cantidadLineas; i++) {
    printf("Linea Simple: %d | Direccion SML: %d | Instrucciones: %d\n",
           tablaLineas[i].numeroSimple,
           tablaLineas[i].direccionSML,
           tablaLineas[i].cantidadInstrucciones);
}

printf("-----------------------------------\n");
printf("Total de instrucciones SML: %d\n",
       cantidadInstruccionesSML);
printf("\nTabla de variables:\n");
printf("-------------------------\n");

for (i = 0; i < 26; i++) {
    if (posicionesVariables[i] != -1) {
        printf("Variable %c -> Posicion %d\n",
               'a' + i, posicionesVariables[i]);
    }
}

printf("-------------------------\n");
printf("\nTabla de constantes:\n");
printf("-------------------------\n");

for (i = 0; i < cantidadConstantes; i++) {
    printf("Constante %d -> Posicion %d\n",
           constantes[i],
           posicionesConstantes[i]);
}

printf("-------------------------\n");
printf("\nMemoria temporal:\n");
printf("-------------------------\n");

for (i = 0; i < cantidadTemporales; i++) {
    printf("Temporal %d -> Posicion %d\n",
           i,
           direccionesTemporales[i]);
}

printf("-------------------------\n");
printf("Total de variables: %d\n", cantidadVariables);

    printf("\nPrograma Simple cargado:\n\n");
	
    for ( i = 0; i < cantidadLineas; i++) {
        printf("%d %s\n",
               programa[i].numero,
               programa[i].instruccion);
    }

    return 0;
}
