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
$ ./genetic -i <instancia> -t <tiempo_max> -a <alfa> --th <umbral> --pop <pob_inicial> \
      --crossover <crossover> --mutation <mutación> --selection <selección> \
      --cross-rate <tasa_crossover> --mut-rate <tasa_mutación> [--tuning]
```

- `-i`: La ruta al archivo de texto con la instancia a probar
- `--th`: El umbral (*threshold*) sobre el que va a correr el algoritmo
- `-a`: El coeficiente de determinismo para el algoritmo ([0, 1])
- `-t`: El tiempo máximo de ejecución en segundos para el algoritmo  (0, \infty)
- `--pop`: Tamaño de la población inicial  (0, \infty)
- `--selection`: Tipo de selección a realizar. Puede tomar uno de los siguientes valores:
    - `0`: Selección por ruleta (*fitness proportionate selection*)
    - `1`: Selección por torneo
    - `2`: Selección aleatoria
- `--crossover`: Tipo de *crossover* a realizar. Puede tomar uno de los siguientes valores:
    - `0`: *Crossover* uniforme
    - `1`: *Crossover* de un punto
    - `2`: *Crossover* de dos puntos
- `--mutation`: Tipo de mutación a realizar. Puede tomar uno de los siguientes valores:
    - `0`: *Bit flipping*
    - `1`: Intercambio (*swap*)
    - `2`: Mezcla (*scramble*)
- `--cross-rate`: Tasa de *crossover* ( [0, 1] )
- `--mut-rate`: Tasa de mutación ( [0, 1] )
- `--tuning`: Si está definido, el programa no imprime resultados parciales por salida estándar.
