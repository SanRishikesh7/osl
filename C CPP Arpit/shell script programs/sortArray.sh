#!/bin/bash

arr=(10 20 15 8 7)
n=${#arr[*]}
echo $n
echo "Original array is: " ${arr[*]}

for (( i=0; i < n; i++ ))
do
	for (( j=0;j < `expr $n - $i - 1`; j++ ))
	do
		if [ ${arr[$j]} -gt ${arr[`expr $j + 1`]} ]; then
			temp=${arr[j]}
			arr[$j]=${arr[`expr $j + 1`]}
			arr[`expr $j + 1`]=$temp
		fi
	done
done

echo "Sorted array is: " ${arr[*]}
