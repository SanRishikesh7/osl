#!/bin/bash

# Function to create a new file
create_file() {
    read -p "Enter the filename: " filename
    touch "$filename"
    echo "Created a new file: $filename"
}

# Function to write into a file
write_to_file() {
    read -p "Enter the filename: " filename
    read -p "Enter text to write: " text
    echo "$text" > "$filename"
    echo "Wrote '$text' to the file: $filename"
}

# Function to read contents line by line
read_line_by_line() {
    read -p "Enter the filename: " filename
    echo "Reading contents line by line from $filename:"
    while IFS= read -r line
    do
        echo "$line"
    done < "$filename"
}

# Function to read contents character by character
read_char_by_char() {
    read -p "Enter the filename: " filename
    echo "Reading contents character by character from $filename:"
    while IFS= read -n 1 char
    do
        echo -n "$char"
    done < "$filename"
    echo
}

# Function to append to a file
append_to_file() {
    read -p "Enter the filename: " filename
    read -p "Enter text to append: " text
    echo "$text" >> "$filename"
    echo "Appended '$text' to the file: $filename"
}

# Function to delete a file
delete_file() {
    read -p "Enter the filename to delete: " filename
    rm "$filename"
    echo "Deleted the file: $filename"
}

# Menu
while true; do
    echo "Menu:"
    echo "1. Create a new file"
    echo "2. Write into a file"
    echo "3. Read contents line by line"
    echo "4. Read contents character by character"
    echo "5. Append to a file"
    echo "6. Delete a file"
    echo "7. Exit"

    read -p "Enter your choice: " choice

    case "$choice" in
        1) create_file ;;
        2) write_to_file ;;
        3) read_line_by_line ;;
        4) read_char_by_char ;;
        5) append_to_file ;;
        6) delete_file ;;
        7) echo "Exiting the program." ; exit ;;
        *) echo "Invalid choice. Please enter a valid option." ;;
    esac
done
