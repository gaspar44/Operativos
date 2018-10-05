#!/bin/bash
clear
echo "Recomendación rápida de restaurante"
echo "-----------"

# Leemos los archivos
IFS=$'\n' registers=($(cat "datos/geoplaces2.csv"))

for (( i = 1; i < ${#registers[@]}; i++ )); 
do
	promedio=0
	placeID=$(echo ${registers[$i]} | cut -d ',' -f 1)

	readedAlcohol=$(echo ${registers[$i]} | cut -d ',' -f 12)
	readedAllowedSmoking=$(echo ${registers[$i]} | cut -d ',' -f 13)
	readedDressCode=$(echo ${registers[$i]} | cut -d ',' -f 14)
	readedAccesibility=$(echo ${registers[$i]} | cut -d ',' -f 15)
	readedPrice=$(echo ${registers[$i]} | cut -d ',' -f 16)
	
	# Recordando que cada una de las variables donde se almacenan los valores deseados por los clientes
	# Es necesario podedr iterar por cada una de las palabras en los arreglos
	# Luego ver si es igual y proceder a sumar para cada variable de la lista
	for item in "${alcohol[@]}"; do
		if [[ $readedAlcohol == ${alcohol[$item]} ]];then
			promedio=$(bc -l <<< $promedio+$pesoAlcohol)
		fi
	done

done
$@
