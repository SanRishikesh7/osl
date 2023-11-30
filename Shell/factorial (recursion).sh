factorial() {
    num=$1
    result=1

    if [ $num -gt 1 ]; then
        for ((i = 2; i <= num; i++)); do
            result=$((result * i))
        done
    fi

    echo $result
}

echo "Enter the number: "
read num
# factorial $num
echo "Factorial of $num is: $(factorial $num)"