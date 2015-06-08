graph.cpp algorithm.cpp main.cpp: Son los sources.

Para compilar:
make
Para ejecutar:
./planning < <infile> > <outfile>

Resultado.txt: Fichero de resultados de la ejecucion del benchmark.

Tiempo.txt: Fichero de tiempos de la ejecucion del benchmark.

!Nota: los 3 scripts estan preparados para ejecutarse
dentro de la carpeta benchmark y que esta a su vez este
dentro del directorio con el binario de planning.!

solvebenchmark.sh: Genera el fichero Resultado.txt.
Para ejecutar: ./solvebenchmark.sh

timebenchmark.sh: Genera el fichero auxiliar Tiempo0.txt.
Para ejecutar: ./timebenchmark.sh

timebenchmark.py: Utiliza Tiempo0.txt y genera Tiempo.txt.
Para ejecutar: ./timebenchmark2.py

