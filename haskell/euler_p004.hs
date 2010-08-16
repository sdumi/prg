-- http://projecteuler.net/index.php?section=problems&id=4
-- A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.
-- Find the largest palindrome made from the product of two 3-digit numbers.

-- we need some files from the previous exercise
--------------------------------------------------------------------
euler_p003 :: Integer -> Integer -> [Integer] -> [Integer]
euler_p003 0 a l = l
euler_p003 1 a l = l
euler_p003 n curTPrime l = if curTPrime <= n
                           then if n `mod` curTPrime == 0
                                then euler_p003 (n `div` curTPrime) curTPrime (l ++ [curTPrime])
                                else euler_p003 n (curTPrime + 1) l
                           else l
primes n = euler_p003 n 2 []
--------------------------------------------------------------------
--
splitNumber :: Integer -> [Integer]
splitNumber n = if n < 10
                then [n]
                else [n `mod` 10] ++ splitNumber (n `div` 10)
--splitNumber _ = []

-- :)
largest_palindrome = head [n | n <- reverse[100*100..999*999], splitNumber n == reverse (splitNumber n)]

-- the actual (incorrect) solution:
-- is incorrect because it returns the largest palindrome made from the product of two 3-digit primes
euler_p004_primes = head [m| m <- map primes [n | n <- reverse[100*100..999*999], splitNumber n == reverse (splitNumber n)], length m == 2 &&  length(splitNumber (head m))==3]

-- the good solution:
euler_p004 = maximum [a*b| a<-reverse[100..999], b<-reverse[100..999], splitNumber (a*b) == reverse (splitNumber (a*b))]


primesList = 2 : filter ((==1) . length . primeFactors) [3,5..]
primeFactors n = factor n primesList
    where
      factor n (p:ps)
          | p*p > n        = [n]
          | n `mod` p == 0 = p : factor (n `div` p) (p:ps)
          | otherwise      = factor n ps
