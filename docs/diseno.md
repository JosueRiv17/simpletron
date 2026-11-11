# Diseño del proyecto Simpletron

## 1. Arquitectura general

El proyecto está dividido en tres módulos principales que trabajan de manera independiente, pero que forman parte de una misma solución:

1. **Simulador Simpletron:** ejecuta programas escritos en instrucciones SML.
2. **Evaluador de expresiones:** procesa y calcula expresiones aritméticas.
3. **Compilador Simple:** transforma programas escritos en el lenguaje Simple a instrucciones SML.

## 2. Organización de archivos

```text
simpletron/
├── README.md
├── docs/
│   ├── requerimientos.md
│   └── diseno.md
├── src/
│   ├── simpletron/
│   │   ├── SIMPLE-TRON.C
│   │   ├── Simpletron.dev
│   │   └── programa.simp
│   ├── expresiones/
│   │   ├── evaluador.c
│   │   └── evaluador.h
│   └── compilador/
│       ├── simple.c
│       └── CompiladorSimple.dev
├── programas/
│   ├── sml/
│   └── simple/
├── pruebas/
│   └── prueba_evaluador.c
└── evidencias/
    ├── ejecuciones/
    └── git-branch/
```

## 3. Descripción de los módulos

### 3.1 Simulador Simpletron

Archivo principal: `SIMPLE-TRON.C`.

Se encarga de cargar, interpretar y ejecutar instrucciones SML. Utiliza una memoria de 1000 posiciones y registros internos para realizar las operaciones.

También incorpora instrucciones adicionales para módulo, exponenciación, manejo de cadenas y operaciones con números decimales.

### 3.2 Evaluador de expresiones

Archivos: `evaluador.c` y `evaluador.h`.

Contiene las funciones encargadas de procesar expresiones aritméticas. Este módulo permite separar la evaluación de operaciones del resto del compilador.

### 3.3 Compilador Simple

Archivo principal: `simple.c`.

Lee programas escritos en el lenguaje Simple, procesa sus instrucciones, valida su contenido y genera el código SML correspondiente.

Utiliza el evaluador de expresiones para procesar las operaciones aritméticas.

## 4. Flujo de funcionamiento

El proceso general del proyecto es el siguiente:

1. El usuario escribe un programa utilizando el lenguaje Simple.
2. El compilador lee y analiza las instrucciones.
3. Se validan las variables, expresiones y condiciones.
4. El evaluador procesa las expresiones aritméticas necesarias.
5. El compilador genera las instrucciones SML.
6. El simulador Simpletron carga y ejecuta el programa SML.

## 5. Decisiones de diseño

- Se dividió el proyecto en módulos para facilitar su organización y mantenimiento.
- El evaluador de expresiones se implementó por separado para reutilizar su funcionalidad en el compilador.
- Se utilizaron archivos de texto para almacenar los programas de entrada y salida.
- Se mantuvieron proyectos independientes en Dev-C++ para evitar conflictos entre las diferentes funciones `main()`.
- Se utilizó Git y GitHub para llevar el control de versiones y conservar los avances del proyecto.

## 6. Herramientas de desarrollo

- Lenguaje C.
- Dev-C++.
- Git.
- GitHub.