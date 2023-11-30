#!/bin/bash

checkFilePermission() {
    if [ -e "$1" ]; then
        echo "File $1 exists"
        
        if [ -L "$1" ]; then
            echo "Type: Symbolic Link"
        elif [ -f "$1" ]; then
            echo "Type: Regular File"
        elif [ -d "$1" ]; then
            echo "Type: Directory"
        elif [ -c "$1" ]; then
            echo "Type: Character Device"
        elif [ -b "$1" ]; then
            echo "Type: Block Device"
        elif [ -p "$1" ]; then
            echo "Type: Named Pipe"
        fi
        
        if [ -r "$1" ]; then
            echo "Read permission is granted"
        else
            echo "Read permission is not granted"
        fi
        
        if [ -w "$1" ]; then
            echo "Write permission is granted"
        else
            echo "Write permission is not granted"
        fi
        
        if [ -x "$1" ]; then
            echo "Execute permission is granted"
        else
            echo "Execute permission is not granted"
        fi
    else
        echo "File $1 does not exist"
    fi
}

echo "Enter a file or directory name: "
read fileName
checkFilePermission "$fileName"
