#!/bin/python3

# Get file hashes recursively

import os
import sys
import hashlib
import colorama as cr
from glob import iglob
from argparse import ArgumentParser

def init(argv):
	parser = ArgumentParser()
	parser.add_argument("-o", dest = "log", required = True, type = str, help = "specify output file")
	parser.add_argument("-r", dest = "rec", action='store_true', help = "execute recursively")
	parser.add_argument("--dir", dest = "dir", type = str, help = "specify working directory")
	parser.add_argument("--glob", dest = "glob", type = str, help = "specify included files as a glob expression")
	return parser.parse_args()

def main(argv):
	args = init(argv)
	if args.glob == None:
		args.glob = "*"
	if args.dir == None:
		args.dir = "./"
	if args.rec:
		args.glob = "**/" + args.glob
	files = iglob(args.dir + args.glob, recursive = True)
	o = open(args.log, "w")

	print(cr.Fore.GREEN + "Hashing starts..." + cr.Fore.YELLOW)
	for i in files:
		if not os.path.isfile(i):
			continue
		print('\tWorking on file "' + i + '"...')
		with open(i, "rb") as f:
			o.write(hashlib.sha256(f.read()).hexdigest() + " | " + i + "\n")
	print(cr.Fore.GREEN + "Hashing done.")
	o.close()



if __name__ == '__main__':
	raise SystemExit(main(sys.argv[1:]))
