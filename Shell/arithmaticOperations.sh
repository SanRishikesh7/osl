#!/bin/bash

# Reading the input
read -p "Enter the first number: " num1
read -p "Enter the second number: " num2

# Performing arithmetic operations
addition=$((num1 + num2))
subtraction=$((num1 - num2))
multiplication=$((num1 * num2))

# Checking if num1 is not zero for division
if [ "$num1" -ne 0 ]; then
    division=$((num1 / num2))
else
    echo "Undefined division by zero"
fi

# Storing the results in respective files
echo "Addition result for $num1 + $num2: $addition" >> "add_result.txt"
echo "Subtraction result for $num1 - $num2: $subtraction" >> "sub_result.txt"
echo "Multiplication result for $num1 * $num2: $multiplication" >> "mul_result.txt"

# Checking if num1 is not zero before storing division result
if [ "$num1" -ne 0 ]; then
    echo "Division result for $num1 / $num2: $division" >> "div_result.txt"
fi
