-- 4.
-- unzip' [('a', 1), ('b', 2)] = ("ab", [1, 2])

unzip'' :: ([a], [b]) -> [(a, b)] -> ([a], [b])
unzip'' l [] = l
unzip'' (a, b) ((c, d):xs) = unzip''(a ++ [c], b ++ [d]) xs
unzip' l = unzip'' ([], []) l
