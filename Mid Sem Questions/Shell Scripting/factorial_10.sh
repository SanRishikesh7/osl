
echo "Enter numbmer: "
read num
factorial=1
i=1
while [ $i -le $num ]
do
	factorial=`expr $factorial \* $i`
	i=`expr $i + 1`
done
echo "Factorial of " $num "is :" $factorial
