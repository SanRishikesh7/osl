arr=()
take_elem(){
	arr=()
	read -p "Enter elements to be entered: " n

	for (( i=0; i<n; i++ )); do
		read -p "Enter element: " num
		arr+=("$num")
	done
}

average(){
	arr=$1
	n=${#arr[*]}
	sum=0
	for (( i=0; i<n; i++ )); do
		sum=`expr $sum + ${arr[i]}`
	done
	echo "Average of given numbers is: " `expr $sum / $n`
}

maxNumber(){
	arr=$1
	n=${#arr[*]}
	max=-1
	for (( i=0; i<n; i++ )); do
		if [ ${arr[i]} -gt $max ]; then
			max=${arr[i]}
		fi
	done

	echo "Maximum number in the given elements is: " $max
}

minNumber(){
	arr=$1
	n=${#arr[*]}
	min=99999
	for (( i=0; i<n; i++ )); do
		if [ ${arr[i]} -lt $min ]; then
			min=${arr[i]}
		fi
	done
	echo "Minimum number in given elements is: " $min
}
#arr=(1 2 3 4 5)
take_elem
echo "Given array elements are: " ${arr[*]}
average ${arr[*]}
maxNumber ${arr[*]}
minNumber ${arr[*]}
