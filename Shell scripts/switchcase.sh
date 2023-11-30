#!/bin/bash
average(){
	count=0
	num=$1
	sum=0
	while [ $num -ne 0 ]; do
		r=`expr $num % 10`
		sum=`expr $sum + $r`
		num=`expr $num / 10`
		count=`expr $count + 1`
	done
	echo "Average is: "  `expr $sum / $count`
}

min(){
	num=$1
	min=9999
	while [ $num -ne 0 ]; do
		r=`expr $num % 10`
		if [ $r -lt $min ];then
			min=$r
		fi
		num=`expr $num / 10`
	done
	echo "Minimum number is: " $min
}

max(){
	num=$1
	max=-1
	while [ $num -ne 0 ];do
		r=`expr $num % 10`
		if [ $r -gt $max ];then
			max=$r
		fi
		num=`expr $num / 10`
	done
	echo "Maximum number is: " $max
}

read -p "Enter number: " num
echo "The number is: " $num

average $num
min $num
max $num
