#!/bin/bash
new_file=""
# Function to create a new file
create_file() {
    echo "Enter the name of the file to create:"
    read new_file
    touch "$new_file"
    echo "File '$new_file' has been created."
}

# Function to read content line by line and write into the file
read_and_write_line_by_line() {
    echo "Enter text line by line (press Ctrl+D to finish):"
    while IFS= read -r line; do
        echo "$line" >> "$new_file"
    done
    echo "Content has been written to '$new_file' line by line."
}

# Function to read content character by character
read_character_by_character() {
    echo -e "\nReading content character by character:"
    while IFS= read -rn1 char; do
        echo -n "$char "
    done < "$new_file"
    echo -e "\nCharacter by character reading completed."
}

# Function to append more content to the file
append_content() {
    echo "Enter text to append to the file:"
    read additional_content
    echo "$additional_content" >> "$new_file"
    echo "Additional content has been appended to '$new_file'."
}

# Function to delete the file
delete_file() {
    rm "$new_file"
    echo "File '$new_file' has been deleted."
}

# Main menu
while true; do
    echo -e "\nMenu:"
    echo "1. Create a new file"
    echo "2. Read content line by line and write into the file"
    echo "3. Read content character by character"
    echo "4. Append more content to the file"
    echo "5. Delete the file"
    echo "6. Exit"
    read -p "Enter your choice (1-6): " choice

    case $choice in
        1) create_file ;;
        2) read_and_write_line_by_line ;;
        3) read_character_by_character ;;
        4) append_content ;;
        5) delete_file ;;
        6) exit ;;
        *) echo "Invalid choice. Please enter a valid option (1-6)." ;;
    esac
done
