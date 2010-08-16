-- http://projecteuler.net/index.php?section=problems&id=7
-- By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6^(th) prime is 13.

-- What is the 10001^(st) prime number?
primesList = 2 : filter ((==1) . length . primeFactors) [3,5..]
primeFactors n = factor n primesList
    where
      factor n (p:ps)
          | p*p > n        = [n]
          | n `mod` p == 0 = p : factor (n `div` p) (p:ps)
          | otherwise      = factor n ps
-- this is because primesList !! 0 == 2 :)
euler_p007 = primesList !! 10000
