
# checkFile(){
# 	if [ -a $1 ]; then
# 		if [ -r $1 ]; then
# 			echo "File has read permission"
# 		else
# 			echo "File dont have read permission"
# 		fi
# 		if [ -w $1 ]; then
# 			echo "File has write permission"
# 		else
# 			echo "File dont have write permission"
# 		fi
# 		if [ -x $1 ]; then
# 			echo "File has execute permission"
# 		else
# 			echo "File dont have execute permission"
# 		fi
# 	else
# 		echo "File not exists"
# 	fi
# }

# echo "Enter file name: "
# read fileName

# checkFile $fileName




echo "Enter the file name: "
read filename

file_type=$(file -b $filename)

file_permission=$(ls -l $filename | awk '{print $1}')

echo "File type: $file_type"
echo "File permission: $file_permission"
