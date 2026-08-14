#!/bin/bash

for i in dataset/*; do
    echo "> Converting webms"
	for h in $i/*.webp; do
		convert "$h" "${h//.webp/.png}" 2> /dev/null && rm "$h" && echo "> > $h"
	done
    echo "> Deduplicating"
    fdupes -d -N "$i"
    echo "> Purging the hidden webms out of spite"
    for h in $i/*;  do
        file -i "$h" 2> /dev/null | grep "webp" && rm "$h" && echo "> > $h"
    done
done
