#!bin/bash

if [ ! "$1" ]
then
    echo "usage: build.sh name"
    return 1
fi

gcc -c -Wall -Wextra -pedantic -ggdb -std=c99 $1.c

gcc $1.o -o $1