#!/bin/bash
i=0
while read link; do
    if [ -z "$link" ]
    then
        echo "Line $(($i+1)) empty"
    else
        echo "Link found in line $(($i+1)), downloading..."
        curl -o audio/$i.mp3 $link &> /dev/null
    fi
    i=$(($i+1))
done < audio.txt