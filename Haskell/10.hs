import Data.List

map' :: (a -> b) -> [a] -> [b]
map' _ []     = []
map' f (x:xs) = f x : map' f xs

filter' :: (a -> Bool) -> [a] -> [a]
filter' _ []     = []
filter' f (x:xs) = if f x then x : filter' f xs else filter' f xs

all' :: (a -> Bool) -> [a] -> Bool
all' _ []     = True
all' f (x:xs) = f x && all' f xs

any' :: (a -> Bool) -> [a] -> Bool
any' _ []     = False
any' f (x:xs) = f x || any' f xs

elem' :: Eq a => a -> [a] -> Bool
elem' e l = any' (\x -> x == e) l

-- HF:
--   hasAny    :: [a] -> [a] -> Bool
--   takeWhile :: ([a] -> [a]) -> [a] -> [a]
--   takewhile odd [1, 3, 5, 8, 9]

hasAny :: Eq a => [a] -> [a] -> Bool
hasAny [] _ = False
hasAny _ [] = False
hasAny (li:lix) lh = (elem' li lh) || (hasAny lix lh)

takeWhile' :: (a -> Bool) -> [a] -> [a]
takeWhile' _ [] = []
takeWhile' f (a:as)
  | f a       = a : takeWhile' f as
  | otherwise = []

dropWhile' :: (a -> Bool) -> [a] -> [a]
dropWhile' _ [] = []
dropWhile' f (a:as)
  | f a       = []
  | otherwise = a : dropWhile' f as

monogram :: [Char] -> [Char]
monogram s = concat (map (\x -> x : ". ") (map head (words s)))

uniq :: Ord a => [a] -> [a]
uniq l = map head (group (sort l))
