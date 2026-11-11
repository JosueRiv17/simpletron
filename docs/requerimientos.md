# Requerimientos del proyecto Simpletron

## 1. Objetivo general

Desarrollar un simulador Simpletron en lenguaje C, ampliar sus instrucciones e integrar un evaluador de expresiones y un compilador de un lenguaje sencillo hacia código SML.

## 2. Requerimientos funcionales

### 2.1 Simulador Simpletron

- RF01. El sistema debe permitir cargar programas desde un archivo `programa.simp`.
- RF02. El sistema debe permitir introducir instrucciones manualmente cuando no se encuentre el archivo.
- RF03. El sistema debe manejar una memoria de 1000 posiciones.
- RF04. El sistema debe interpretar instrucciones mediante un código de operación y un operando.
- RF05. El sistema debe realizar operaciones aritméticas básicas.
- RF06. El sistema debe permitir saltos condicionales e incondicionales.
- RF07. El sistema debe calcular módulo y exponenciación.
- RF08. El sistema debe permitir operaciones con números decimales.
- RF09. El sistema debe permitir entrada y salida de cadenas de caracteres.
- RF10. El sistema debe mostrar resultados y mensajes de error durante la ejecución.
- RF11. El sistema debe detectar situaciones como la división entre cero.

### 2.2 Evaluador de expresiones

- RF12. El sistema debe evaluar expresiones aritméticas.
- RF13. Debe respetar la precedencia de operadores y el uso de paréntesis.
- RF14. Debe permitir utilizar variables dentro de las expresiones.
- RF15. Debe reconocer operaciones y reportar expresiones inválidas.

### 2.3 Compilador del lenguaje Simple

- RF16. El compilador debe leer instrucciones escritas en el lenguaje Simple.
- RF17. Debe reconocer instrucciones de entrada, asignación, impresión y finalización.
- RF18. Debe procesar condiciones y saltos.
- RF19. Debe evaluar expresiones aritméticas dentro de las asignaciones.
- RF20. Debe generar instrucciones SML a partir del programa Simple.
- RF21. Debe validar variables no inicializadas y destinos de salto inexistentes.
- RF22. Debe reportar errores cuando encuentre instrucciones o condiciones inválidas.

## 3. Requerimientos no funcionales

- RNF01. El proyecto debe estar desarrollado en lenguaje C.
- RNF02. El código debe estar organizado en módulos independientes.
- RNF03. Los programas deben poder compilarse mediante los proyectos configurados en Dev-C++.
- RNF04. El sistema debe mostrar mensajes claros para identificar errores.
- RNF05. El código fuente debe mantenerse en un repositorio GitHub.
- RNF06. La documentación debe explicar la estructura y funcionamiento general del proyecto.

## 4. Herramientas utilizadas

- Lenguaje de programación: C.
- Entorno de desarrollo: Dev-C++.
- Control de versiones: Git.
- Repositorio remoto: GitHub.