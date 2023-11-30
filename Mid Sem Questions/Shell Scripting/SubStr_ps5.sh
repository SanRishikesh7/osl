#!/bin/bash

# Input string
input_string="This is a sample string with sample text. Sample is repeated."

# Substring to count
substring="sample"

# Use grep with -o option to count occurrences
count=$(echo "$input_string" | grep -io "$substring" | wc -l)

echo "The substring '$substring' appears $count times in the input string."