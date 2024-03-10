#!/bin/python3

input = [
	"   # # ",
	"/''--__",
	"_---'''",
]

o = []

for i in input:
	for h in i:
		#print(f" '{h}' (#{round(ord(h)/127, 2)});", end='')
		print(f"{round(ord(h)/127, 2)}, ", end='')
	#print('')

