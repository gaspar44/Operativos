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
	fi

	formatLineCounter=$(cat $1 | awk ' { print $2 } ' | wc | awk '{ print $2 } ')

	if [[ $formatLineCounter -gt 0 ]]; then
		echo "El archivo no cumple con el formato"
	fi

	parsedVariables=($(cat $1 | cut -d "=" -f 1 | awk ' { print $1 } ' | awk ' { print tolower($0) }'))
	parsedValues=($(cat $1 | cut -d "=" -f 2 | awk ' { print $1 } '))

	if [[ ! ${#parsedValues[@]} -eq ${#parsedVariables[@]} ]];then
		echo "hay un error en el archivo, por favor verifique los parametros"
	fi

	#for (( i = 0; i < ${#parsedVariables[@]}; i++ ));do
	#	if [[ parsedVariables[i]]]


fi

#$@