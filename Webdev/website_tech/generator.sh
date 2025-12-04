#!/bin/bash

# generator.sh

OUTPUT="data.txt"

while true; do 
	rm $OUTPUT
	for i in {0..7}; do 
		(tr -dc A-Za-z0-9 </dev/urandom | head -c 8; echo ' : '$RANDOM ) >> $OUTPUT
	done
	sleep 5
done
