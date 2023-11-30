
checkFile(){
	if [ -a $1 ]; then
		if [ -r $1 ]; then
			echo "File has read permission"
		else
			echo "File dont have read permission"
		fi
		if [ -w $1 ]; then
			echo "File has write permission"
		else
			echo "File dont have write permission"
		fi
		if [ -x $1 ]; then
			echo "File has execute permission"
		else
			echo "File dont have execute permission"
		fi
	else
		echo "File not exists"
	fi
}

read -p "Enter the filr name: " fileName

checkFile $fileName
