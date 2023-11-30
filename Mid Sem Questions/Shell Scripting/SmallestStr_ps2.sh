#!/bin/bash

# Directory to search for files
directory="/home/siddhesh"

# Check if the directory exists
if [ ! -d "$directory" ]; then
    echo "Error: Directory does not exist."
    exit 1
else
    #print the message that file exists
    echo "Directory exists."
fi

# initialize empty array for storing the file names
fileName=()
finalName=()

for file in "$directory"/*; do
    #checking if the file item is file not a directory
    if [ -f "$file" ]; then
        #storing the file name in the array
        fileName+=("$file")
    fi
done


#printing the file names in the fileName array
echo "The files in the directory are: "
for file in "${fileName[@]}"; do
    echo "$file"
done

#only taking the real file name and not the path
#using substring to get the file name
for file in "${fileName[@]}"; do
    #getting the length of the file name
    length=${#file}
    #getting the last index of the file name
    lastindex=$(($length-1))
    #declaring the variable for storing the tempName
    tempName=""
    #traversing from last index till I get '/' character
    while [ "${file:$lastindex:1}" != "/" ]; do
        #storing the character in the tempName
        tempName="${file:$lastindex:1}$tempName"
        #decrementing the last index
        lastindex=$lastindex-1
    done
    #storing the tempName in the finalName array
    finalName+=("$tempName")
done

#printing the file names in the finalName array
echo "The files in the directory are: "
for file in "${finalName[@]}"; do
    echo "$file"
done

#printing the smallest file name in the finalName array
smallest=""
echo "==========================="
echo "The smallest file name is: "
for file in "${finalName[@]}"; do
    len=${#file}
    if [ "${#smallest}" == 0 ]; then
        smallest="$file"
    elif [ "$len" -lt "${#smallest}" ]; then
        smallest="$file"
    fi
done
echo "$smallest"


