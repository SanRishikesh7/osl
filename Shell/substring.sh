
echo "Enter the main string: "
read str1

echo "Enter substring: "
read str2

len1=`echo $str1 | wc -c`
len2=`echo $str2 | wc -c`

len1=`expr $len1 - 1`
len2=`expr $len2 - 1`
flag=0
for(( i=1;i<=len2;i++ ))
do
	len3=`expr $len2 + $i - 1`
	sub1=`echo $str1 | cut -c$i-$len3`
	if [[ $sub1 == $str2 ]]; then
		flag=1
	fi
done

if [[ $flag == 1 ]]; then
	echo "Substring"
else
	echo "Not substring"
fi

