#!/bin/bash
clear
echo "Recomendación rápida de restaurante"
echo "-----------"

# Leemos los archivos
IFS=$'\n' registers=($(cat "datos/geoplaces2.csv"))
declare -a max=()

for (( i = 1; i < ${#registers[@]}; i++ )); 
do
	promedio=0
	placeID=$(echo ${registers[$i]} | cut -d ',' -f 1)

	readedAlcohol=$(echo ${registers[$i]} | cut -d ',' -f 12)
	readedAllowedSmoking=$(echo ${registers[$i]} | cut -d ',' -f 13)
	readedDressCode=$(echo ${registers[$i]} | cut -d ',' -f 14)
	readedAccesibility=$(echo ${registers[$i]} | cut -d ',' -f 15)
	readedPrice=$(echo ${registers[$i]} | cut -d ',' -f 16)

	for item in "${alcohol[@]}"; do
		if [[ $readedAlcohol == ${item} ]];then
			promedio=$(bc -l <<< $promedio+$pesoAlcohol)
			break
		fi
	done
	
	for item in "${dressCode[@]}"; do
		if [[ $readedDressCode == ${item} ]];then
			promedio=$(bc -l <<< $promedio+$pesoDressCode)
			break
		fi
	done

	for item in "${accessibility[@]}"; do
		if [[ $readedAccessibility == ${accessibility[$item]} ]];then
			promedio=$(bc -l <<< $promedio+$pesoAccessibility)
			break
		fi
	done

	
	if [[ ${promedio} > ${promedioMax} ]]; then
		max=${registers[$i]}

	elif [[ ${promedio} = ${promedioMax} ]];then
		max+=${registers[$i]}
	fi

	for item in "${price[@]}"; do
		if [[ $readedPrice == ${item} ]];then
			promedio=$(bc -l <<< $promedio+$pesoPrice)
			break
		fi
	done

	for item in "${smokingArea[@]}"; do
		if [[ $readedAllowedSmoking == ${item} ]];then
			promedio=$(bc -l <<< $promedio+$pesoSmoingArea)
			break
		fi
	done

	for item in "${dressCode[@]}"; do
		if [[ $readedDressCode == ${item} ]];then
			promedio=$(bc -l <<< $promedio+$pesoDressCode)
			break
		fi
	done

	for item in "${accessibility[@]}"; do
		if [[ $readedAccessibility == ${accessibility[$item]} ]];then
			promedio=$(bc -l <<< $promedio+$pesoAccessibility)
			break
		fi
	done

	if [[ $promedio -gt $promedioMax ]]; then
		max=${registers[$i]}

	else if [[ $promedio -eq $promedioMax ]];then
		max+=${registers[$i]}
	fi
done

if [[ ${#max[@]} == 1 ]]; then
	echo $max

else 
	elementToShow=$(($RANDOM % ${#max[@]}))
	echo ${max[$elementToShow]}
fi

$@