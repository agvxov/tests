#!/bin/bash

MWIDTH=0
MHIGHT=0
for i in *.jpg *.jpeg *.png; do
    W=$(identify "$i" 2> /dev/null | cut -d " " -f 3 | cut -d "x" -f 1)
    [[ $W -gt $MWIDTH ]] && MWIDTH=$W
done
for i in *.jpg *.jpeg *.png; do
    H=$(identify "$i" 2> /dev/null | cut -d " " -f 3 | cut -d "x" -f 2)
    [[ $H -gt $MHIGHT ]] && MHIGHT=$H
done

ffmpeg \
	-f concat \
	-safe 0 \
	-i <(sed -e '1,/^### INPUT SECTION ###/ d' -e "s/\$pwd/'${PWD//\//\\\/}/" $0) \
	-vf "scale=force_original_aspect_ratio=1,pad=${MWIDTH}:${MHIGHT}" \
	-plays 0 \
	out.apng

exit
### INPUT SECTION ###
file '$pwd/<some_image>.jpg'
duration 3
file '$pwd/<some_image>.jpg'
duration 3
file '$pwd/<some_image>.jpg'
duration 3
file '$pwd/<some_image>.jpg'
duration 1
file '$pwd/<some_image>.jpg'
duration 2
file '$pwd/<some_image>.jpg'
