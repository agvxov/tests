#!/bin/python3

g = 17
n = 2
U = list(range(1, 10))

N = []

for i in range(0, n-1):
	N.append(min(U))
	U.remove(N[i])

N.append(g-int(sum(N)))

print(N)
