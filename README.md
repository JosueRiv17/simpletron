# Simpletron

Simulador de una computadora hipotética implementado en lenguaje C.

El proyecto parte de una implementación básica de Simpletron y posteriormente incorpora diferentes mejoras para ampliar sus capacidades de memoria, procesamiento y manejo de datos.

## Características

### Versión original

* Memoria de instrucciones y datos.
* Acumulador.
* Registro de instrucción.
* Código de operación y operando.
* Instrucciones básicas de entrada y salida.
* Carga y almacenamiento de valores.
* Operaciones aritméticas.
* Saltos condicionales.
* Manejo de errores.
* Vaciado de memoria al finalizar.

### Mejoras implementadas

1. **Carga de programas desde archivo**

   * Lectura automática desde `programa.simp`.
   * Carga manual cuando el archivo no existe.
   * Validación de valores.

2. **Memoria de 1000 posiciones**

   * Direcciones de `000` a `999`.
   * Operandos de tres dígitos.
   * Formato de instrucciones `CCAAA`.

3. **Operación módulo**

   * Nueva instrucción para calcular el residuo de una división.

4. **Exponenciación**

   * Nueva instrucción para calcular potencias.
   * Control de desbordamiento.

5. **Salida con salto de línea**

   * Nueva instrucción para imprimir una nueva línea.

6. **Entrada de cadenas**

   * Almacenamiento de cadenas mediante valores ASCII.
   * La primera posición almacena la longitud.
   * Cada posición siguiente almacena la posición y el código ASCII del carácter.

7. **Salida de cadenas**

   * Lectura de la longitud.
   * Conversión de códigos ASCII a caracteres.
   * Impresión secuencial de la cadena.

8. **Soporte de punto flotante**

   * Memoria independiente para valores `float`.
   * Acumulador flotante.
   * Entrada y salida de números decimales.
   * Suma, resta, multiplicación y división.
   * Validación de división entre cero.

## Formato de instrucciones

Las instrucciones utilizan el formato:

```text
CCAAA
```

Donde:

* `CC` = código de operación.
* `AAA` = dirección de memoria.

Ejemplo:

```text
10120
```

significa:

```text
10 → entrada
120 → dirección de memoria
```

Otro ejemplo:

```text
99000
```

significa:

```text
99 → detener el programa
000 → operando
```

## Almacenamiento de cadenas

Las cadenas utilizan el formato:

```text
XX YYY
```

Donde:

* `XX` = posición del carácter o longitud.
* `YYY` = código ASCII.

Por ejemplo, para `"Mundo"`:

```text
040 → 05 000
041 → 01 077
042 → 02 117
043 → 03 110
044 → 04 100
045 → 05 111
```

## Compilación

El proyecto utiliza lenguaje C y la biblioteca matemática.

Con GCC:

```bash
gcc simpletron.c -o simpletron -lm
```

En Windows:

```bash
gcc simpletron.c -o simpletron.exe -lm
```

## Ejecución

Si existe el archivo:

```text
programa.simp
```

el simulador intenta cargarlo automáticamente.

Si no existe, el programa permite introducir las instrucciones manualmente.

## Proyecto académico
Se utilizará una memoria flotante independiente (float memoriaFloat[1000]) para almacenar valores de punto flotante. Se utilizará un acumulador flotante independiente (float acumuladorFloat). 
Las instrucciones 15–23 permitirán entrada, salida y operaciones aritméticas con valores flotantes. La memoria entera y las instrucciones originales permanecerán sin cambios.

Proyecto realizado como práctica de programación y ampliación de un simulador Simpletron.
