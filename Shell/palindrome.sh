check(){
	str=$1
	j=`expr ${#str} - 1`
	i=0
	isPalin=true

	while [ $i -le $j ]; do
		if [ ${str:$i:1} != ${str:$j:1} ]; then
			isPalin=false
			break
		fi

		i=$((i + 1))
		j=$((j + 1))

	done

	if [ $isPalin == true ]; then
		echo "It is Palindrome"
	else
		echo "It is not Palindrome"
	fi
}
echo "Enter String or number to check it is Palindrome or not : "
read str

check $str
