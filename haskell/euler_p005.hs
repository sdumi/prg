-- http://projecteuler.net/index.php?section=problems&id=5
-- 2520 is the smallest number that can be divided by each of the numbers from 1 to 10 without any remainder.

-- What is the smallest positive number that is evenly divisible by all of the numbers from 1 to 20?

isGood n target= let modn x = n `mod` x
           in sum (map modn [1..target]) == 0

-- naive solution:
-- this one is very computational intensive...
euler_p005 = head[n | n <- [2520..], isGood n 20]

-- optimised solution
-- fast (but not mine: http://www.haskell.org/haskellwiki/Euler_problems/1_to_10)
euler_p005_optim = foldr1 lcm [1..20]