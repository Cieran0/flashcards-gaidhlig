#!/bin/bash
i=0
rm audio/*.mp3
while read link; do
    if [ -z "$link" ]
    then
        echo "Line $(($i+1)) empty"
    else
        echo "Link found in line $(($i+1)), downloading..."
        curl -o audio/$i.u.mp3 $link &> /dev/null
    fi
    i=$(($i+1))
done < audio.txt

for ((x = 0 ; x < i ; x++)); do
    ffmpeg -ss 1 -i audio/$x.u.mp3 -c copy audio/$x.mp3 &> /dev/null
    rm audio/$x.u.mp3 &> /dev/null
done
