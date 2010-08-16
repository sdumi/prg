-- http://projecteuler.net/index.php?section=problems&id=10
-- The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.
-- Find the sum of all the primes below two million.


primesList = 2 : filter ((==1) . length . primeFactors) [3,5..]
primeFactors n = factor n primesList
    where
      factor n (p:ps)
          | p*p > n        = [n]
          | n `mod` p == 0 = p : factor (n `div` p) (p:ps)
          | otherwise      = factor n ps

makePrimeList nr (x:xs)
    | x < nr = (x : makePrimeList nr xs)
    | otherwise = []

euler_p010_ = sum (makePrimeList 2000000 primesList)
euler_p010  = sum (takeWhile (<2000000) primesList)