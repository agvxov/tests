#!/bin/bash
# NOTE: technically a find command is better,
#        but this is much cleaner if you dont have thousands of files
#        and or spaces in their names
shopt -s globstar
for i in **/*; do
    DIM=$(identify $i | cut -d ' ' -f 3)
    H=$(echo $DIM | cut -d x -f 1)
    W=$(echo $DIM | cut -d x -f 2)
    AREA=$(expr $H '*' $W)
    echo "$i: $DIM $AREA"
done
