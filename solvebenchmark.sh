#!/bin/bash
rm Resultado.txt
touch Resultado.txt
for file in *
do
	echo "$file"
  output="$(../planning < $file)"
  echo "$file $output" >> Resultados.txt
  echo "done!"
done
