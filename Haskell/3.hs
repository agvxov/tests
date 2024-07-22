f :: Num a => a -> a -> a
f a b = (+) a b

in_r :: Int -> Int -> Int -> Bool
in_r min max x = x >= min && x <= max

g = (>) 5

in_rr min max x =
	let
		l = x >= min
		h = x <= max
	in l && h


in_rr2 min max x = l && h
	where
		l = x >= min
		h = x <= max

recf n acc
	| n <= 1 = acc
	| otherwise = recf (n-1) * (n * acc)

factr n = f n 1
	where
		f n acc
			| n <= 1 = acc
			| otherwise = f (n-1) (n * acc)

-- fact 3 =
-- 	| n <= 1 = 1
-- 	| True = n * fac2 (n - 1)
