and' True True = True
and' _    _    = False
--
and'' (True, True) = True
and'' (   _,    _) = False
--
add' (a, b) (c, d) = ((+) a b, (+) b c)


or' False False = False
or' _     _     = True


xor' :: Bool -> Bool -> Bool
xor' a b = not (a == b)


t = ((10, 11), (13, 14))
f ((a, b), (c, d)) = a
((a, b), (c, d)) = t


bin_add 0 0 = (0, 0)
bin_add 0 1 = (0, 1)
bin_add 1 0 = (0, 1)
bin_add 1 1 = (1, 0)


calc (a, (o), b) = (o) a b


sum' :: [Int] -> Int
sum' [] = 0
sum' (x:xs) = x + (sum' xs)

-- HF: in - list; out - odds
