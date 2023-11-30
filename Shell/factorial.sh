echo "Enter a number:"
read number

result=1;

for ((i = 1; i <= $number; i++)); do
        result=$((result * i))
    done

echo "Factorial of $number is: $result"

