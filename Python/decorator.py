#!/bin/python3
def print_canary():
	print('''   .-.    \n'''
	    + '''  /'v'\   \n'''
	    + ''' (/   \)  \n'''
	    + '''='="="===<\n'''
	    + '''mrf|_|    \n''',
		end=''
		)

myBirdFunction = print_canary
myBirdFunction()

def print_with_yellow(func):
	def wrapper(*args, **kwargs):
		print("\033[33m")
		r = func()
		print("\033[0m")
		return r
	return wrapper

myBirdFunction = print_with_yellow(print_canary)
myBirdFunction()
