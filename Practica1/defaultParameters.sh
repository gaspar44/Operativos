#!/bin/bash
# Definición de los parámetros por defecto
if [[ -z $1 ]];then
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
fi

$@