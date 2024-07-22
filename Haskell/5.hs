import Data.Char (toUpper)

headInt :: [Int] -> Int
headInt (x:_) = x

tailInt :: [Int] -> [Int]
tailInt (x:xs) = xs

nullInt :: [Int] -> Bool
nullInt [] = True
nullInt _  = False

isSingleton :: [Int] -> Bool
isSingleton [x] = True
isSingleton  _  = False

toUpperFirst :: [Char] -> [Char]
toUpperFirst [] = []
toUpperFirst (x:xs)  = toUpper x : xs

isLetter :: Char -> Bool
isLetter x = elem x ['A'..'z']

compTest :: Char -> [Char]
compTest x = [x..'z']

mountain :: Int -> [Int]
mountain x = [1..x] ++ [x - 1, x - 2 .. 1]

divisors :: Int -> [Int]
divisors n = [d | d <- [1..n], mod n d == 0]
