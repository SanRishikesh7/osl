
checkPalindrome(){
	str=$1
	j=`expr ${#str} - 1`
	i=0
	isPalin=true
	while [ $i -le $j ]; do
		if [ ${str:$i:1} != ${str:$j:1} ]; then
			isPalin=false
			break
		fi

		i=`expr $i + 1`
		j=`expr $j - 1`
	done
	if [ $isPalin == true ]; then
		echo "String is Palindrome"
	else
		echo "String is not Palindrome"
	fi
}
echo "Enter String: "
read str

checkPalindrome $str
