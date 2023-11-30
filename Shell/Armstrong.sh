echo "Enter Number: "
read num
org=$num
arm=0
echo $org
while [ $num -ne 0 ]
do
    r=$((num % 10))
    arm=$((arm + ($r*$r*$r)))
    num=`expr $num / 10`
done

if [ $org -eq $arm ]; then
    echo "It is Armstrong"
else
    echo "It is not Armstrong"
fi
