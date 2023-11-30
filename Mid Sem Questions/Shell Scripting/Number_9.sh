#!/bin/bash

# Function to calculate the sum of digits
sum_of_digits() {
    num=$1
    sum=0

    while [ $num -gt 0 ]; do
        digit=`expr $num % 10`
        sum=`expr $sum + $digit`
        num=`expr $num / 10`
    done

    echo "Sum of digits: $sum"
}

# Function to reverse the number
reverse_number() {
    num=$1
    reverse=0

    while [ $num -gt 0 ]; do
        r=`expr $num % 10`
        reverse=`expr $reverse \* 10 + $r`
        num=`expr $num / 10`
    done

    echo "Reverse number is: " $reverse 
}

# Main script
read -p "Enter a number: " input_number

sum_of_digits $input_number
reverse_number $input_number
