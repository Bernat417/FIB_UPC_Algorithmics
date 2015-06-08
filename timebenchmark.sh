#!/bin/bash
rm Tiempo0.txt
touch Tiempo0.txt

for file in instance*
do
	echo $file
	START=$(date +%s.%N)
	../planning < $file
	END=$(date +%s.%N)

	runtime=$(echo "$END - $START" | bc)
	echo "$runtime" >> Tiempo0.txt
	echo "done"            	
done
