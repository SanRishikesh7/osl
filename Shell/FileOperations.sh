#!/bin/bash

DATABASE_FILE="database.txt"

# Function to create a new record in the database
create_record() {
    read -p "Enter name: " name
    read -p "Enter email: " email
    last_id=$(tail -n 1 "$DATABASE_FILE" | cut -d '|' -f 1)
    new_id=$((last_id + 1))
    echo "$new_id|$name|$email" >> "$DATABASE_FILE"
    echo "Record created successfully."
}

# Function to read records from the database
read_records() {
    cat "$DATABASE_FILE"
}

# Function to update a record in the database
update_record() {
    read -p "Enter record ID to update: " id
    read -p "Enter new name: " name
    read -p "Enter new email: " email

    # Use temporary file to update the record
    temp_file=$(mktemp)
    awk -v id="$id" -v name="$name" -v email="$email" 'BEGIN {FS=OFS="|"} $1==id {$2=name; $3=email}1' "$DATABASE_FILE" > "$temp_file"
    
    # Overwrite the original file with the updated data
    mv "$temp_file" "$DATABASE_FILE"

    echo "Record updated successfully."
} 

# Function to delete a record from the database
delete_record() {
    read -p "Enter record ID to delete: " id
    awk -v id="$id" 'BEGIN {FS=OFS="|"} $1!=id' "$DATABASE_FILE" > "$DATABASE_FILE.tmp"
    mv "$DATABASE_FILE.tmp" "$DATABASE_FILE"
    echo "Record deleted successfully."
}

# Main menu
while true; do
    echo "1. Create Record"
    echo "2. Read Records"
    echo "3. Update Record"
    echo "4. Delete Record"
    echo "5. Exit"
    read -p "Enter your choice: " choice

    case $choice in
        1) create_record ;;
        2) read_records ;;
        3) update_record ;;
        4) delete_record ;;
        5) exit ;;
        *) echo "Invalid choice. Please try again." ;;
    esac
done