#!/bin/bash
rm Resultados.txt
touch Resultados.txt
for file in *
do
	echo "$file"
  output="$(../planning < $file)"
  echo "$file $output" >> Resultados.txt
  echo "done!"
done
