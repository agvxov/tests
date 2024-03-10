#!/bin/python3

import sys
import getopt
import os
from pathlib import Path
import subprocess

ARCHIVE_TYPES = [
	".zip",
	".rar",
	".7z"
]
MAX_OUTPUT_LEN = 150

input_path = ""
do_delete = False

def usage(name):
	print('''{script} [options]
	-i <path>  : specify input dir
	-d         : do delete
	-h         : print help and quit'''\
	.format(script=name))

def opts(argv):
	global input_path, do_delete
	try:
		opts, args = getopt.getopt(argv[1:], 'i:dh')
	except getopt.GetoptError as e:
			print("Unkown option. Quiting.")
			exit(1)
	for opt, arg in opts:
		if opt == '-i':
			input_path = arg
		elif opt == '-d':
			do_delete = True
		elif opt == '-h':
			usage(argv[0])
			exit(0)

def is_password_protected(file):
	command = ['7z', 't', '-p', file]
	process = subprocess.run(command, stdout=subprocess.PIPE, stderr=subprocess.DEVNULL)
	try:
		process.wait()
	except:
		pass
	return 0 != process.returncode

def extract(file):
	if is_password_protected(file):
		#print('Ignoring ', file, '.', sep='')
		return
	global do_delete
	output_dir = str(file.parent) + '/' + str(file.stem)
	try:
		os.mkdir(output_dir)
	except:
		pass
	output_option = '-o' + str(output_dir)
	command = ['7z', 'x', file, output_option]
	try:
		print('Extracting: ', file, '... ', sep='', end='')
		process = subprocess.Popen(command, stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL, stdin=subprocess.PIPE)
		process.communicate(input='Y\n'.encode())
		process.wait()
		if process.returncode == 0:
			print('Success.')
			if do_delete:
				os.remove(file)
		else:
			print('Fail.')
	except:
		print('\nError while forking 7z. Is it installed correctly?')

def scandir(dir_):
	#print('scandir', dir_)
	global MAX_OUTPUT_LEN
	global ARCHIVE_TYPES
	if len(str(dir_)) >= MAX_OUTPUT_LEN:
		return
	for entry in Path(dir_).iterdir():
		if entry.is_dir():
			scandir(entry)
		else:
			for t in ARCHIVE_TYPES:
				if t == entry.suffix:
					extract(entry)

def main(argv):
	global input_path, do_delete
	opts(argv)
	if input_path == '':
		print("No input directory specified. Quiting.")
		exit(1)
	scandir(input_path)

if __name__ == "__main__":
	main(sys.argv)
