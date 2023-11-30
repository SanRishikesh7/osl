echo "Enter Number: "
read num
sum=0
while [ $num -ne 0 ]
do
	r=$((num % 10))
	sum=$((sum + $r))
	num=`expr $num / 10`
done
echo "Sum is: " $sum





