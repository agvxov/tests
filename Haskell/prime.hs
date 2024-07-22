isprime i = [ k | k <- [2..i-1], mod i k == 0 ] == []

primes = [ n | n <- [1..], isprime n ]

-- ###

allPositive l = null [ n | n <- l, n < 0]
-- HF:
range a b
	| a < b = [a..b]
	| a > b = [ (+) ((-) a n) 1 | n <- [b..a]]
	| otherwise = [a]

