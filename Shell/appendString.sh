#!/bin/bash

#append content of one file to another character by character
#and line by line 

#read the file name from the user
echo "Enter the file name to be appended: "
read file_name

echo "Enter the file name to append to : "
read append_to

#check if the file exists
if test -f $file_name; then
    if test -f $append_to; then
        #append the content of file1 to file2
        while IFS= read -r -n 1 char; do
            echo -n "$char" >> $append_to
        done < $file_name
    fi
fi