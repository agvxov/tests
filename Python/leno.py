#!/bin/python3

bias = 0.52
r_bias = 1 - bias

R = [0, 1, 2, 3]

N = len(R)

def p(n):
	if n == 0:
		return r_bias * (N-1)
	return bias * (N-1-n) * r_bias * n

sum = 0
for i in R:
	k = p(i)
	sum += k
	print(f"p({i}) -> {k}")

print(sum)
