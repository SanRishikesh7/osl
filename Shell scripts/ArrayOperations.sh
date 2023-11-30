average() {
    local arr=("$@")
    n=${#arr[*]}
    sum=0
    for ((i = 0; i < n; i++)); do
        sum=$((sum + arr[i]))
    done
    echo "Average of given numbers is: $((sum / n))"
}

maxNumber() {
    local arr=("$@")
    n=${#arr[*]}
    max=-1
    for ((i = 0; i < n; i++)); do
        if [ ${arr[i]} -gt $max ]; then
            max=${arr[i]}
        fi
    done
    echo "Maximum number in the given elements is: $max"
}

minNumber() {
    local arr=("$@")
    n=${#arr[*]}
    min=99999
    for ((i = 0; i < n; i++)); do
        if [ ${arr[i]} -lt $min ]; then
            min=${arr[i]}
        fi
    done
    echo "Minimum number in given elements is: $min"
}

echo "Enter the elements of the array:"
read -a arr

echo "Array : " ${arr[*]}

while true; do
    echo "Menu:"
    echo "1. Calculate Average"
    echo "2. Find Maximum"
    echo "3. Find Minimum"
    echo "4. Exit"
    echo "Enter your choice: " 
    read choice

    case $choice in
        1)
            average "${arr[@]}"
            ;;
        2)
            maxNumber "${arr[@]}"
            ;;
        3)
            minNumber "${arr[@]}"
            ;;
        4)
            exit 0
            ;;
        *) 
            echo "mkc"
            ;;
    esac
done
