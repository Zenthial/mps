#!bin/bash

if [ ! "$1" ]
then
    echo "usage: clean.sh name"
    return 1
fi

rm -rf $1.o
rm -rf $1