# Proyecto Simpletron

Proyecto académico desarrollado en lenguaje C que implementa un simulador Simpletron, un evaluador de expresiones aritméticas y un compilador de un lenguaje sencillo hacia instrucciones SML.

El objetivo es ampliar las funciones del Simpletron original e integrar herramientas que permitan escribir programas, evaluarlos y ejecutarlos en el simulador.

## 1. Estructura del proyecto

```text
simpletron/
│
├── README.md
│
├── docs/
│   ├── requerimientos.md
│   └── diseno.md
│
├── src/
│   ├── simpletron/
│   │   ├── SIMPLE-TRON.C
│   │   ├── Simpletron.dev
│   │   ├── programa.simp
│   │   └── version-original/
│   │
│   ├── expresiones/
│   │   ├── evaluador.c
│   │   └── evaluador.h
│   │
│   └── compilador/
│       ├── simple.c
│       └── CompiladorSimple.dev
│
├── programas/
│   ├── sml/
│   │   └── programa.simp
│   └── simple/
│       └── programa.simple
│
├── pruebas/
│   └── prueba_evaluador.c
│
└── evidencias/
    ├── ejecuciones/
    └── git-branch/
```

## 2. Módulos del proyecto

### 2.1 Simulador Simpletron

Archivo principal: `src/simpletron/SIMPLE-TRON.C`

Implementa una computadora hipotética con las siguientes características:

- Memoria de 1000 posiciones.
- Acumulador y registros de control.
- Carga automática de programas desde `programa.simp`.
- Entrada manual de instrucciones cuando no existe el archivo.
- Validación de instrucciones y valores.
- Operaciones aritméticas.
- Saltos condicionales.
- Operación módulo.
- Exponenciación.
- Entrada y salida de cadenas mediante códigos ASCII.
- Soporte para números de punto flotante.
- Control de errores, incluyendo división entre cero.

La versión anterior se conserva en `src/simpletron/version-original/`.

### 2.2 Evaluador de expresiones

Archivos:

- `src/expresiones/evaluador.c`
- `src/expresiones/evaluador.h`

Este módulo permite evaluar expresiones aritméticas y se utiliza también dentro del compilador.

Entre sus funciones se encuentran:

- Operaciones de suma, resta, multiplicación y división.
- Uso de paréntesis.
- Evaluación de expresiones con diferentes niveles de prioridad.
- Manejo de variables.
- Operaciones de potencia.
- Detección de errores en expresiones.

La prueba independiente se encuentra en `pruebas/prueba_evaluador.c`.

### 2.3 Compilador del lenguaje Simple

Archivo principal: `src/compilador/simple.c`

Permite procesar programas escritos en un lenguaje sencillo y generar instrucciones SML para ejecutarlas en Simpletron.

Incluye:

- Instrucciones `INPUT`, `LET`, `PRINT` y `END`.
- Operaciones aritméticas y expresiones con paréntesis.
- Condiciones `IF`.
- Saltos mediante `GOTO`.
- Ciclos y estructuras de control mediante saltos.
- Uso de variables y constantes.
- Validación de variables inicializadas.
- Detección de destinos de salto inexistentes.
- Generación de código SML.

El evaluador se integra mediante `evaluador.c` y `evaluador.h`.

## 3. Formato de instrucciones SML

Las instrucciones del simulador utilizan el formato:

```text
CCAAA
```

Donde:

- `CC`: código de operación.
- `AAA`: dirección de memoria u operando.

Ejemplo:

```text
10012
```

Representa una instrucción de entrada utilizando la dirección de memoria 012.

Otro ejemplo:

```text
99000
```

Representa la instrucción de detener la ejecución (`HALT`).

El simulador también incorpora instrucciones adicionales para operaciones con números flotantes, cadenas y otras funciones.

## 4. Programas de prueba

Los programas de ejemplo se encuentran en:

| Archivo | Descripción |
|---|---|
| `programas/sml/programa.simp` | Programa de prueba escrito directamente en SML. |
| `src/simpletron/programa.simp` | Programa utilizado para probar el simulador desde su proyecto de Dev-C++. |
| `programas/simple/programa.simple` | Programa de ejemplo para probar el compilador. |
| `pruebas/prueba_evaluador.c` | Prueba independiente del evaluador de expresiones. |

## 5. Compilación y ejecución

El proyecto fue desarrollado y probado utilizando **Dev-C++**.

Los módulos tienen proyectos independientes porque cada uno contiene su propia función `main()` o se integra de manera diferente.

### Simulador Simpletron

1. Abrir `src/simpletron/Simpletron.dev`.
2. Compilar y ejecutar el proyecto.
3. El simulador buscará automáticamente el archivo `programa.simp` en su directorio de trabajo.
4. Si no encuentra el archivo, permitirá introducir las instrucciones manualmente.

### Compilador Simple

1. Abrir `src/compilador/CompiladorSimple.dev`.
2. Verificar que estén incluidas las unidades `simple.c` y `evaluador.c`.
3. Compilar y ejecutar.
4. El compilador procesa el programa escrito en `programas/simple/programa.simple` utilizando la ruta configurada para el proyecto.

### Prueba del evaluador

Para ejecutar la prueba independiente, crear un proyecto de consola en Dev-C++ e incluir:

- `pruebas/prueba_evaluador.c`
- `src/expresiones/evaluador.c`

No se debe agregar `evaluador.h` como unidad compilable.

**Importante:** Los tres proyectos deben compilarse por separado. No se deben unir sus archivos fuente en un solo proyecto porque existen funciones `main()` independientes.

## 6. Evidencias

La carpeta `evidencias/` contiene capturas de las ejecuciones del programa y del trabajo realizado con Git.

- `evidencias/ejecuciones/`: pruebas y resultados de ejecución.
- `evidencias/git-branch/`: ramas, commits y evidencia del control de versiones.

## 7. Control de versiones

El proyecto utiliza Git y GitHub para registrar los cambios y mantener versiones separadas.

Repositorio:

https://github.com/JosueRiv17/simpletron

Ramas principales:

- `main`: versión integrada del proyecto.
- `simpletronv2`: rama utilizada para desarrollar mejoras del simulador Simpletron.

## 8. Herramientas utilizadas

- Lenguaje C.
- Dev-C++.
- Git.
- GitHub.

## 9. Integrantes

Josué Rivera Flores

## 10. Propósito académico

Este proyecto permite aplicar conceptos de programación estructurada, manejo de memoria, evaluación de expresiones, estructuras de control, compilación, simulación de instrucciones y control de versiones.
