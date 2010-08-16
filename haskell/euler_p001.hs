-- http://projecteuler.net/index.php?section=problems&id=1
-- If we list all the natural numbers below 10 that are multiples of 3 or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
--
-- Find the sum of all the multiples of 3 or 5 below 1000.


-- Solution:

-- this is just a simple test :)
sumList (x:xs) = x + sumList xs
sumList []     = 0

euler_p001 (x:xs) = let myx = if ((mod x 3) == 0) || ((mod x 5) == 0)
                              then x 
                              else 0
                    in myx + euler_p001 xs
euler_p001 [] = 0

-- tail recursive
euler_p001_tail (x:xs) result = let myx = if ((mod x 3) == 0) || ((mod x 5) == 0)
                                          then x 
                                          else 0
                                in euler_p001_tail xs (myx + result)

euler_p001_tail [] result = result

-- oneliner
euler_p001_liner = sum [n | n <- [1..999], (mod n 3 ==0) || (mod n 5 == 0)]

-- right way to do it:
sumDivisibles n target = let p = target `div` n
                         in (n * p * (p + 1)) `div` 2

euler_p001_right target = (sumDivisibles 3 target) + (sumDivisibles 5 target) - (sumDivisibles 15 target)