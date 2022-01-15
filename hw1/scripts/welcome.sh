#!/bin/bash

#1
echo "My home path is: $HOME"

#2
echo "Files in my HOME:"
for file in $HOME/*
do
    if [ -d $file ]
    then
        echo "Directory: $file"
    else
        echo "File: $file"
    fi
done

#3
mkdir tmp$$

#4
mkdir tmp$$/Courses

#5
cd tmp$$/Courses

#6
mkdir cs243

#7
function recursive_directory_print() {
    echo "Directory: $1"
    for file in $1/*
    do
        if [ -d $file ]
        then
            recursive_directory_print $file
        else
            echo "File: $file"
        fi
    done
}

echo "My tmp folder:"

cd ../../
recursive_directory_print tmp$$

cd tmp$$/Courses

#8

echo ""

#9

echo "Translation steps: Preprocessing, Compilation, Assembly, Linking"

#10

echo "Warning flags required for gcc in this course: -Wall -Wextra -pedantic"

#11

echo "C dialect flags required for gcc in this course: -std=c99"

#12

echo "Debug flags required for gcc in this course: -ggdb"

# 13
echo "LoginID: $LOGNAME"