-- http://projecteuler.net/index.php?section=problems&id=12

-- The sequence of triangle numbers is generated by adding the natural numbers. So the 7^(th) triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:
-- 1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...
-- Let us list the factors of the first seven triangle numbers:

--      1: 1
--      3: 1,3
--      6: 1,2,3,6
--     10: 1,2,5,10
--     15: 1,3,5,15
--     21: 1,3,7,21
--     28: 1,2,4,7,14,28

-- We can see that 28 is the first triangle number to have over five divisors.
-- What is the value of the first triangle number to have over five hundred divisors?
import Data.List

primesList = 2 : filter ((==1) . length . primeFactors) [3,5..]
primeFactors n = factor n primesList
    where
      factor n (p:ps)
          | p*p > n        = [n]
          | n `mod` p == 0 = p : factor (n `div` p) (p:ps)
          | otherwise      = factor n ps

divisors_ k n
    | k <= ((n `div` 2) + 1) = if (n `mod` k == 0)
                               then k : divisors_ (k+1) n
                               else divisors_ (k+1) n
    | otherwise = []
divisors n = (n:(divisors_ 1 n))

triangleList = map triangle [1..]
triangle n = (n * (n + 1)) `div` 2

--primeFactors in problem_3
problem_12 = head $ filter ((> 500) . nDivisors) triangleNumbers
  where nDivisors n = product $ map ((+1) . length) (group (primeFactors n))    
        triangleNumbers = scanl1 (+) [1..]