#!/bin/bash

reverseStr() {
    str=$1
    revStr=""
    len=${#str} - 1

    for ((i = len; i >= 0; i--)); do
        revStr="${revStr}${str:i:1}"
    done

    echo "$revStr"
}

reverseStr $1


