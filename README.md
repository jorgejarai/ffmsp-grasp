# `ffmsp-greedy`

Proyecto para resolver el problema FFMSP utilizando una metaheurística GRASP.

## Instrucciones para compilar

Este programa requiere CMake para ser compilado.

Para compilar el programa, ejecute los siguientes comandos:

```console
$ mkdir build
$ cd build
$ cmake ..
$ make
```

## Ejecución

```console
$ ./build/grasp -i <instancia> -t <tiempo_max> [-a <alfa>] [-u <umbral>]
```
- `-i`: La ruta al archivo de texto con la instancia a probar
- `-t`: El umbral (*threshold*) sobre el que va a correr el algoritmo
- `-a`: Coeficiente de determinismo (0.9 por defecto)
- `-u`: Umbral para la selección de candidatos (0.8 por defecto)
