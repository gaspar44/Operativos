#!/bin/bash
# Definición de los parámetros por defecto
if [[ -z $1 ]];then  # Si es vacío el string
	pesoPrecio=0.4
	pesoSmokingArea=0.1
	pesoAlcohol=0.2
	pesoDressCode=0.1
	pesoAccessibility=0.2

	declare -a alcohol=("Wine-Beer")
	declare -a precio=("medium")
	declare -a smokingArea=("not-permitted" "none")
	
	declare -a dressCode=("informal" "casual")
	declare -a accessibility=("partially" "completely")

else
	if [[ ! -f $1 ]];then
		echo "archivo no encontrado"
		exit 1

	else 
		echo "el archivo a usar es: $1"
	fi

	formatLineCounter=$(cat $1 | awk ' { print $2 } ' | wc | awk '{ print $2 } ')

	if [[ $formatLineCounter -gt 0 ]]; then
		echo "El archivo no cumple con el formato"
		exit 1
	fi

	parsedVariables=($(cat $1 | cut -d "=" -f 1 | awk ' { print $1 } ' | awk ' { print tolower($0) }'))
	parsedValues=($(cat $1 | cut -d "=" -f 2 | awk ' { print $1 } '))

	if [[ ! ${#parsedValues[@]} -eq ${#parsedVariables[@]} ]];then
		echo "hay un error en el archivo, por favor verifique los parametros"
		exit 1
	fi

	for (( i = 0; i < ${#parsedVariables[@]}; i++ ));do

		if [[ ${parsedVariables[i]} = "price" ]];then
			auxiliarPrice=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "dress" ]]; then
			auxiliarDressCode=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "alcohol" ]]; then
			auxiliarAlcohol=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "smoking" ]]; then
			auxiliarSmokingArea=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "accessibility" ]]; then
			auxiliarAccessibility=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "peso_price" ]]; then
			pesoPrecio=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "peso_dress" ]]; then
			pesoDressCode=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "peso_alcohol" ]]; then
			pesoAlcohol=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "peso_smoking" ]]; then
			pesoSmokingArea=${parsedValues[i]}

		elif [[ ${parsedVariables[i]} = "peso_accessibility" ]]; then
			pesoAccessibility=${parsedValues[i]}
		else	
			echo "Hubo error, please try again"
			exit 1
		fi
	done
source ./opcion4.sh 1

fi

#$@