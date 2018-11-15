#!/bin/bash
source ./defaultParameters.sh $1

while [[ true ]]; do
	echo "1. Recomendación rápida de restaurante"
	echo "2. Recomendación detallada de restaurante"
	echo "3. Consultar parámetros de recomendación"
	echo "4. Ajustar parámetros recomendación"
	echo "5. Salir"
	echo "-----------------------------------------"
	read -p "Introduzca una opción (1/2/3/4/5) " opcion

	case $opcion in

		1)
			source ./opcion1.sh;;

		2)
			source ./opcion2.sh ;;
		
		3)
			source ./opcion3.sh ;;

		4)
			source ./opcion4.sh ;;

		5)
			clear
			exit 0 ;;

		*)
			clear
			echo "error, pruebe de nuevo" ;;
	esac

done