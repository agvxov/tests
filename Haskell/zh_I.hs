-- Kovács Dávid - AGVXOV
--
-- A. csoport
-- Zárthelyi dolgozat
-- Funkcionális nyelvek



-- 1.) Adjuk meg azt a függvényt, amely első paramétere egy elem és egy bool.
-- Az elemet csak akkor fűzzük a második paraméterként kapott lista elejére, ha a bool igaz.


condAddToList :: (a, Bool) -> [a] -> [a]
--condAddToList (x, y) z = if y then x : z else z
condAddToList (x, y) z
  | y = x : z
  | otherwise = z


-- 2.) Adjuk meg azt a függvényt, amely két egész számot kap, és előállítja a köztük értelmezett
-- intervallumot! Abban az esetben, ha az első argumentum nagyobb, mint a második, akkor üres
-- listát adjon vissza!

interval :: Int -> Int -> [Int]
interval x y = if x > y then [] else [x..y]

-- 3.)Adjuk meg azt a függvényt, amely egy rendezett párt állít elő egy listából. A pár első eleme a
-- lista első eleme, a pár második eleme pedig a lista farok része legyen. Feltételezhetjük, hogy a
-- lista nem üres.

headTail :: [a] -> (a, [a])
headTail (x:xs) = (x, xs)
