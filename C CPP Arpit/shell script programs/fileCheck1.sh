#!/bin/bash
# Check if a file path is provided as an argument
if [ $# -ne 1 ]; then
  echo "Usage: $0 <file_path>"
  exit 1
fi

file_path="$1"

# Check if the file exists
if [ ! -e "$file_path" ]; then
  echo "Error: File does not exist."
  exit 1
fi

# Check file type
if [ -d "$file_path" ]; then
  file_type="directory"
elif [ -f "$file_path" ]; then
  file_type="regular file"
elif [ -L "$file_path" ]; then
  file_type="symbolic link"
else
  file_type="unknown"
fi
# Check file permissions
permission=$(ls -l "$file_path" | cut -d ' ' -f 1)
user_permission=${permission:1:3}
group_permission=${permission:4:3}
others_permission=${permission:7:3}

echo "File Type: $file_type"
echo "Permissions:"
echo "User: $user_permission"
echo "Group: $group_permission"
echo "Others: $others_permission"
checkFile() {
file_type="f"
        if [ -a $1 ]; then
                if [ -r $1 ]; then
                        echo "File is in read Mode"
                else
                        echo "File is not in read Mode"
                fi

                if [ -w $1 ]; then
                        echo "File is in write Mode"
                else
                        echo "File is not in write Mode"
                fi
                else
                        echo "File is not in execute Mode"
                fi
        else
                echo "File no exist"
        fi

        # Check file type
if [ -d $1 ]; then
  file_type="directory"
elif [ -f "$file_path" ]; then
  file_type="regular file"
elif [ -L "$file_path" ]; then
  file_type="symbolic link"
else
  file_type="unknown"
fi
        echo "The file type is : " $file_type
}

echo "Enter the file name : "
read fileName
checkFile $fileName
