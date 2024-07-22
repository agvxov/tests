-- ### Definions ###
sum' :: [Int] -> Int
sum' [n] = n
sum' (x:xs) = x + sum' xs

avg :: [Int] -> Float
avg l = (/) (fromIntegral (sum' l)) (fromIntegral (length l))

powerOfN :: (Num a, Integral b) => a -> b -> [a]
powerOfN base max = [base ^ d | d <- [0 .. max]]

timePairs :: [(Int, Int)]
timePairs = [(h, m) | h <- [0 .. 23], m <- [0 .. 59]]

-- ### Tests ###
main :: IO ()
main = do
	putStrLn "\ESC[32mSum 1..100:\ESC[0m"
	putStrLn (show (sum' [1..100]))
	putStrLn "\ESC[32mAverage of [1, 2]:\ESC[0m"
	putStrLn (show (avg [1, 2]))
	putStrLn "\ESC[32mAverage of [2, 4, 6, 8, 100]:\ESC[0m"
	putStrLn (show (avg [2, 4, 6, 8, 100]))
	putStrLn "\ESC[32mPowers of 2 up to 2^100:\ESC[0m"
	putStrLn (show (powerOfN 2 100))
	putStrLn "\ESC[32mPowers of 10 up to 10^20:\ESC[0m"
	putStrLn (show (powerOfN 10 20))
	putStrLn "\ESC[32mAll hour-minute pairs:\ESC[0m"
	putStrLn (show timePairs)
