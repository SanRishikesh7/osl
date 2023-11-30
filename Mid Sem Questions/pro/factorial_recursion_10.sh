#!/bin/bash

factorial_recursive() {
    if [ $1 -le 1 ]; then
        echo 1
    else
        local sub_factorial
        sub_factorial=$(factorial_recursive $(( $1 - 1 )))
        echo $(( $1 * $sub_factorial ))
    fi
}


read -p "Enter a number: " num

if [[ $num -lt 0 ]]; then
    echo "Factorial is not defined for negative numbers."
elif [[ $num -eq 0 ]]; then
    echo "Factorial of 0 is 1."
else
    result=$(factorial_recursive $num)
    echo "Factorial of $num is $result."
fi
