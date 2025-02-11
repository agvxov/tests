#!/bin/sh

echo test

# this is what i would like to execute beforehand,
#  except it requires root, but the building fails under root (in general)
# mount --bind "$APPDIR/header.txt" "/var/db/repos/gentoo/"

./hw-hardcoded-path.out
