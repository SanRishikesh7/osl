

# The result variable is an array
ls_output=$(ls -l | grep -E '^[-dls]' | awk '{print $1, $NF}')

echo $ls_output

regular_files=()
directories=()
symbolic_links=()
total_size=0

while IFS= read -r line; do 
    #extract the file type and name
    file_type=${line:0:1}
    file_name=$(echo $line | awk '{print $2}')

    
    case "$file_type" in
        "-")
            echo "Regular File: $file_name"
            regular_files+=("$file_name")
            total_size+=$(wc -c < "$file_name")
            ;;
        "d")
            echo "DIR: $file_name /"
            directories+=("$file_name")
            ;;
        "l")
            echo "LINK: $file_name @"
            symbolic_links+=("$file_name")
            ;;
    esac
done <<< "$ls_output"

#printing the summary information
echo "Total Directories: ${#directories[@]}"
echo "Total Regular Files: ${#regular_files[@]}"
echo "Total Symbolic Links: ${#symbolic_links[@]}"
echo "Total Size of regular files in byte: $total_size"
# The result of the ls -l command is stored in the result variable.
