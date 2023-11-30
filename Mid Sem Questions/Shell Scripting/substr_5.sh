#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Usage: $0 <main_string> <substring>"
    exit 1
fi

main_string="$1"
substring="$2"

len1=${#main_string}
len2=${#substring}
count=0

for ((i = 0; i <= len1 - len2; i++)); do
    sub1="${main_string:$i:len2}"
    if [ "$sub1" == "$substring" ]; then
        count=$((count + 1))
    fi
done

if [ $count -gt 0 ]; then
    echo "The substring '$substring' occurs $count times in the main string."
else
    echo "The substring '$substring' does not occur in the main string."
fi
