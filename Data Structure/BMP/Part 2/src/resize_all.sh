#!/bin/bash

if [ $# -eq 3 ] 
then
    echo "Resizing..."
    for i in `ls $1`
    do
        if [ ! -d $2 ] 
        then
            mkdir $2
        fi
        ./out/resize -p $3 -o "$2/${i%.*}Resized.bmp" -i "$1/$i" -v
    done
    echo "Resizing complete"
else
    echo "Usage: $0 input_directory output_directory psf_filename"
fi
