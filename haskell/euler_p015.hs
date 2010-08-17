-- http://projecteuler.net/index.php?section=problems&id=15
-- Starting in the top left corner of a 2×2 grid, there are 6 routes (without backtracking) to the bottom right corner.

-- How many routes are there through a 20×20 grid?


-- Solution in haskell taken from: http://www.haskell.org/haskellwiki/Euler_problems/11_to_20
-- not sure I currently understand it :)

problem_15  = iterate (scanl1 (+)) (repeat 1) !! 20 !! 20
problem_15_ = product [21..40] `div` product [2..20]