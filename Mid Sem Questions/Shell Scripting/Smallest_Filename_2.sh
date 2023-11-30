#!/bin/bash

# Ensure the current directory is set
current_dir=$(pwd)

# Initialize variables to store the smallest file and its length
smallest_file=""
smallest_length=-1

find_smallest_by_content() {
    current_dir=$(pwd)
    smallest_file=""
    smallest_length=-1

    for file in "$current_dir"/*; do
        if [ -f "$file" ]; then
            file_length=$(wc -c < "$file")

            if [ "$smallest_length" -eq -1 ] || [ "$file_length" -lt "$smallest_length" ]; then
                smallest_file="$file"
                smallest_length="$file_length"
            fi
        fi
    done

    if [ "$smallest_length" -ne -1 ]; then
        echo "The smallest file by content length is:"
        echo "File: $smallest_file"
        echo "Length: $smallest_length characters"
    else
        echo "No files found in the current directory."
    fi
}

find_smallest_by_filename() {
    current_dir=$(pwd)
    smallest_file=""
    smallest_length=-1

    for file in "$current_dir"/*; do
        if [ -f "$file" ]; then
            filename_length=${#file}

            if [ "$smallest_length" -eq -1 ] || [ "$filename_length" -lt "$smallest_length" ]; then
                smallest_file="$file"
                smallest_length="$filename_length"
            fi
        fi
    done

    if [ "$smallest_length" -ne -1 ]; then
        echo "The smallest file by filename length is:"
        echo "File: $smallest_file"
        echo "Length: $smallest_length characters"
    else
        echo "No files found in the current directory."
    fi
}


# Main menu
while true; do
    echo "Select an option:"
    echo "1. Find Smallest File by Content Length"
    echo "2. Find Smallest File by Filename Length"
    echo "3. Exit"
    read -p "Enter your choice: " choice

    case $choice in
        1) find_smallest_by_content ;;
        2) find_smallest_by_filename ;;
        3) exit ;;
        *) echo "Invalid choice. Please try again." ;;
    esac
done