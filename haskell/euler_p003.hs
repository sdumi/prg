-- http://projecteuler.net/index.php?section=problems&id=3
-- The prime factors of 13195 are 5, 7, 13 and 29.

-- What is the largest prime factor of the number 600851475143 ?

--list_p 0 = []
--list_p n = (n:list_p (n-1))

--my_reverse :: [a] -> [a]
--my_reverse [] = []
--my_reverse (x:xs) = my_reverse xs ++ [x]

-- call it:
-- euler_p003 600851475143 2 []
-- ==> [71,839,1471,6857]

-- this is a very naive implementation of finding the prime factors of a number
-- ex: euler_p003 5726623063 2 []
-- will take a really long time to complete :)
euler_p003 :: Integer -> Integer -> [Integer] -> [Integer]
euler_p003 0 a l = l
euler_p003 1 a l = l
euler_p003 n curTPrime l = if curTPrime <= n
                           then if n `mod` curTPrime == 0
                                then euler_p003 (n `div` curTPrime) curTPrime (l ++ [curTPrime])
                                else euler_p003 n (curTPrime + 1) l
                           else l