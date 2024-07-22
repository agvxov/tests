module Tipusok where

inc a = a + 1

inc2 :: Int -> Int
inc2 a = inc (inc a)

-- div :: Fractional a => a -> a -> a
-- div a b = a / b

shw :: n -> n
shw n = n

sho0, sho1 :: Int
sho0 = maxBound
sho1 = minBound

i :: Num a => a -> a
i a = a

-- 
sumt 0 = 0
sumt n = n + sumt (n - 1)

--
curryer a b = a / b
