#!/bin/bash

#directory to search for files
directory="/home/siddhesh"

#check if the file exists
if test ! -d $directory; then
    echo "Directory $directory does not exists"
    exit 1
fi

#creating empty array
files=()

for file in "$directory"/*; do
    #check if the file is a regular file
    if test -f $file; then
        #add file to the array
        files+=($(basename "$file"))
    fi
done


#check if the array is empty
if test ${#files[@]} -eq 0; then
   echo "No files found"
fi

echo "the files are:"
for file in "${files[@]}"; do
    echo "$file"
    echo -e "\n"
done

#finding the smallest file
smallest=${files[0]}

for file in "${files[@]}"; do
   len=${#file}
   if test $len -lt ${#smallest}; then
         smallest=$file
    fi
done

echo "The smallest file is: $smallest"


#finding the smallest by content

smallestByContent() {
    smallest=${files[0]}
    tempwc=$(wc -c < "$smallest")

    for file in ${files[@]}; do
        wc=$(wc -c < "$file")
        if test $wc -lt $tempwc; then
            smallest=$file
            tempwc=$wc
        fi
    done

    echo "The smallest file by content is: $smallest"
    echo "with word count: $tempwc"


}

smallestByContent