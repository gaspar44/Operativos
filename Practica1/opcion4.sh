#/bin/bash
clear
echo "Ajustar parámetros recomendación"
echo "-----"

unset alcohol
unset precio
unset smokingArea
unset dressCode
unset accessibility
declare -a alcohol
declare -a precio
declare -a smokingArea
declare -a dressCode
declare -a accessibility

read -p "Indique valores para price [M,H,L]: " auxiliarPrice
auxiliarIterator=$(echo ${auxiliarPrice} | awk -F "," '{print NF-1}')


for (( i = 0; i < $((auxiliarIterator + 1)); i++ )); do
	temp=$(echo $auxiliarPrice | cut -d "," -f $((i+1)))

	if [[ $temp = "M" ]]; then
		precio[i]="medium"

	elif [[ $temp = "L" ]]; then
		precio[i]="low"

	elif [[ $temp = "H" ]]; then
		precio[i]="high"

	else
		echo "VALOR $temp no valido"
		clear
		return
	fi
done


read -p "Indique valores para dress_code [I,C,F]: " auxiliarDressCode
auxiliarIterator=$(echo ${auxiliarPrice} | awk -F "," '{print NF-1}')


for (( i = 0; i < $((auxiliarIterator + 1)); i++ )); do
	temp=$(echo $auxiliarDressCode | cut -d "," -f $((i+1)))

	if [[ $temp = "I" ]]; then
		dressCode[i]="informal"

	elif [[ $temp = "C" ]]; then
		dressCode[i]="casual"

	elif [[ $temp = "F" ]]; then
		dressCode[i]="formal"

	else
		echo "VALOR $temp no valido"
		clear
		return
	fi
done


read -p "Indique valores para alcohol [N,W,F]: " auxiliarAlcohol
auxiliarIterator=$(echo ${auxiliarPrice} | awk -F "," '{print NF-1}')


for (( i = 0; i < $((auxiliarIterator + 1)); i++ )); do
	temp=$(echo $auxiliarAlcohol | cut -d "," -f $((i+1)))

	if [[ $temp = "N" ]]; then
		alcohol[i]="No_Alcohol_Served"

	elif [[ $temp = "W" ]]; then
		alcohol[i]="Wine-Beer"

	elif [[ $temp = "F" ]]; then
		alcohol[i]="Full_Bar"

	else
		echo "VALOR $temp no valido"
		clear
		return
	fi
done


read -p "Indique valores para smoking_area [0,B,P,S,N]: " auxiliarSmokingArea
auxiliarIterator=$(echo ${auxiliarPrice} | awk -F "," '{print NF-1}')


for (( i = 0; i < $((auxiliarIterator + 1)); i++ )); do
	temp=$(echo $auxiliarSmokingArea | cut -d "," -f $((i+1)))

	if [[ $temp = "0" ]]; then
		smokingArea[i]="none"

	elif [[ $temp = "B" ]]; then
		smokingArea[i]="only_at_bar"

	elif [[ $temp = "P" ]]; then
		smokingArea[i]="permitted"

	elif [[ $temp = "S" ]]; then
		smokingArea[i]="section"

	elif [[ $temp = "N" ]]; then
		smokingArea[i]="not-permitted"

	else
		echo "VALOR $temp no valido"
		clear
		return
	fi
done


read -p "Indique valores para accessibility [N,P,C]: " auxiliarAccessibility
auxiliarIterator=$(echo ${auxiliarAccessibility} | awk -F "," '{print NF-1}')


for (( i = 0; i < $((auxiliarIterator + 1)); i++ ));do
	temp=$(echo $auxiliarAlcohol | cut -d "," -f $((i+1)))

	if [[ $temp = "N" ]]; then
		accessibility[i]="no_accessibility"

	elif [[ $temp = "P" ]]; then
		accessibility[i]="partially"

	elif [[ $temp = "C" ]]; then
		accessibility[i]="completely"

	else
		echo "VALOR $temp no valido"
		clear
		return
	fi
done


$@