#/bin/bash
clear
echo "Recomendación detallada de restaurante"
echo "------"

source ./opcion4.sh 1
source ./opcion1.sh 1

read -p "Presione cualquier tecla para continuar" variable
source ./defaultParameters $configurationFile