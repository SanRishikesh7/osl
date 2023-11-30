
num=$1
sum=0
while [ $num -ne 0 ]
do
	r=`expr $num % 10`
	sum=`expr $sum + $r`
	num=`expr $num / 10`
done
echo "Sum is: " $sum





