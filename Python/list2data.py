#!/bin/python3
# NOTE: i write this to make interacting with GNU Plot less painful
from sys import argv

l = eval(argv[1])

with open('data.txt', 'w') as f:
	for i in l: f.write(str(i) + '\n')
