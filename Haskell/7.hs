sum' :: [Int] -> Int
sum' [] = 0
sum' (x:xs) = x + sum' xs

last' :: [Int] -> Int
last' [] = undefined
last' [x] = x
last' (x:xs) = last' xs

and' :: [Bool] -> Bool
and' [] = True
and' (x:xs) = x && and' xs

-- repeat' :: 
repeat' a = [a, a..]

--replicate' x [y] =
--  if x > 0
--  then []
--  else undefined

insert' y [] = [y]
insert' y (x:xs) =
  if y < x
  then y : x : xs
  else x : insert' y xs
