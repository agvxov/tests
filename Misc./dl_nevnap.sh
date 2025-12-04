#!/bin/bash

OUTPUT="nev_napok.json"

echo "{" > $OUTPUT
for i in $(seq -f "%02g" 1 1 12); do
	for h in $(seq -f "%02g" 1 1 31); do	# cheap hack, but works
		DATA=$(curl https://api.nevnapok.eu/nap/${i}-${h} | jq | tail -n +2 | head -n -1 )
		DATA=${DATA%,}
		[ -z "${DATA}" ] && continue
		echo "$DATA"',' >> $OUTPUT
	done
done
echo "}" >> $OUTPUT
