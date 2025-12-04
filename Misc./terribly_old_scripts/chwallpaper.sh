#!/bin/bash

# Set wallpaper randomly to a picture from ${WALLPAPER_DIR}
# The monitor to be tempared is hardcoded; see the last line

WALLPAPER_DIR="/home/anon/Master/Personal/Wallpaper/Changing/"

cd $WALLPAPER_DIR

# for some reason i cant make this line work with a glob. oh, well...
IMAGE="$(ls | shuf | head -n 1)"

#echo "$IMAGE"

IMAGE=${WALLPAPER_DIR}${IMAGE}

xfconf-query -c xfce4-desktop --property /backdrop/screen0/monitorDVI-D-1/workspace0/last-image --set $IMAGE
