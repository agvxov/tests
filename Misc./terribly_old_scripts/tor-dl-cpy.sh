#!/bin/bash

DL_FOLDER="/home/anon/Downloads"
TOR_DL_FOLDER="/home/anon/.local/share/torbrowser/tbb/x86_64/tor-browser_en-US/Browser/Downloads"

for i in $TOR_DL_FOLDER/*; do
	cp "$i" "$DL_FOLDER/"
done
