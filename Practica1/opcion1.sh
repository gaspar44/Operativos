#!/bin/bash


if [[ -z $1 ]]; then
	clear
	echo "Recomendación rápida de restaurante"
	echo "-----------"
fi


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

	rating=($(cat datos/rating_final.csv | grep $placeID | cut -d ',' -f 3))
	promedioRating=0

	for element in "${rating[@]}"; do
		promedioRating=$(($promedioRating + $element))
	done

	promedioRating=$(bc -l <<< $promedioRating/${#rating[@]})

	if [[ $promedioRating > 1 ]]; then
		for item in "${alcohol[@]}"; do
			if [[ $readedAlcohol == ${item} ]];then
				promedio=$(bc -l <<< $promedio+$pesoAlcohol)
				finalAlcohol=${item}
				
			fi
		done


		for item in "${price[@]}"; do
			if [[ $readedPrice == ${$item} ]];then
				promedio=$(bc -l <<< $promedio+$pesoPrice)
				finalPrice=${item}
				
			fi
		done

		for item in "${smokingArea[@]}"; do
			if [[ $readedDressCode == ${item} ]];then
				promedio=$(bc -l <<< $promedio+$pesoSmokingArea)
				finalSmokingArea=${item}
				
			fi
		done
		
		for item in "${dressCode[@]}"; do
			if [[ $readedDressCode == ${item} ]];then
				promedio=$(bc -l <<< $promedio+$pesoDressCode)
				finalDressCode=${item}
				
			fi
		done


		for item in "${accessibility[@]}"; do
			if [[ $readedAccessibility == ${item} ]];then
				promedio=$(bc -l <<< $promedio+$pesoAccessibility)
				finalAccessibility=${item}
				
			fi
		done

		if [[ ${promedio} > ${promedioMax} ]]; then
			max=${registers[$i]}
			promedioMax=${promedio}

		elif [[ ${promedio} = ${promedioMax} ]];then
			max+=${registers[$i]}
		fi
	fi

done

if [[ ${#max[@]} == 1 ]]; then
	echo "Restaurante recomendado: " $(echo $max | cut -d "," -f 5) 0$promedioMax 
	echo Alcohol: $finalAlcohol, price: $finalPrice, smokingArea: $finalSmokingArea, dressCode: $finalDressCode, accessibility: $finalAccessibility 

else 
	elementToShow=$(($RANDOM % ${#max[@]}))
	echo "Restaurante recomendado: " $(echo ${max[$elementToShow]} | cut -d ',' -f 5) 0$promedioMax
	echo Alcohol: $finalAlcohol, price: $finalPrice, smokingArea: $finalSmokingArea, dressCode: $finalDressCode, accessibility: $finalAccessibility 

fi

echo ".................."