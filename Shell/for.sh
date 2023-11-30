#!/bin/bash

# Function to calculate average
function average() {
  sum=0
  count=0
  for num in $@; do
    sum=$(expr $sum + $num)
    count=$(expr $count + 1)
  done
  avg=$(expr $sum / $count)
  echo "Average: $avg"
}

# Function to find max
function max() {
  max=$1
  for num in $@; do
    if [ $num -gt $max ]; then
      max=$num
    fi
  done
  echo "Max: $max"
}

# Function to find min
function min() {
  min=$1
  for num in $@; do
    if [ $num -lt $min ]; then
      min=$num
    fi
  done
  echo "Min: $min"
}

echo "Enter the numbers: "
read -a numbers

average "${numbers[@]}"
max "${numbers[@]}"
min "${numbers[@]}"
