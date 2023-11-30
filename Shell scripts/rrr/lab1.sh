#!/bin/bash

# Input numbers
read -p "Enter first number: " num1
read -p "Enter second number: " num2

# Perform arithmetic operations
addition=$((num1 + num2))
subtraction=$((num1 - num2))
multiplication=$((num1 * num2))

# Check if the second number is not zero to avoid division by zero
if [ "$num2" -ne 0 ]; then
  division=$((num1 / num2))
else
  division="Undefined (Division by zero)"
fi

# Store results in respective files with a timestamp
echo "Addition Result for $num1 + $num2: $addition" >> "addition_results.txt"
echo "Subtraction Result for $num1 - $num2: $subtraction" >> "subtraction_results.txt"
echo "Multiplication Result for $num1 * $num2: $multiplication" >> "multiplication_results.txt"
echo "Division Result for $num1 / $num2: $division" >> "division_results.txt"

echo "Results have been appended to respective files with timestamp:"
echo "addition_results.txt, subtraction_results.txt, multiplication_results.txt, division_results.txt"