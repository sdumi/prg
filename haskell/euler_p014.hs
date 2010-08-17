-- http://projecteuler.net/index.php?section=problems&id=14
-- The following iterative sequence is defined for the set of positive integers:

-- n → n/2 (n is even)
-- n → 3n + 1 (n is odd)

-- Using the rule above and starting with 13, we generate the following sequence:
-- 13 → 40 → 20 → 10 → 5 → 16 → 8 → 4 → 2 → 1

-- It can be seen that this sequence (starting at 13 and finishing at 1) contains 10 terms. Although it has not been proved yet (Collatz Problem), it is thought that all starting numbers finish at 1.

-- Which starting number, under one million, produces the longest chain?
-- NOTE: Once the chain starts the terms are allowed to go above one million.
import Data.List   

numbers = [999999,999997..500000]
genSequence 1 = [1]
genSequence n
    | n `mod` 2 == 0 = (n : genSequence (n `div` 2))
    | otherwise = (n : genSequence (3 * n + 1))
sequences = map genSequence numbers
sequencesLengths = map length sequences
maxLength = maximum sequencesLengths

findMax max maxPos curPos (x:xs)
    | max < x = findMax x curPos (curPos+1) xs
    | otherwise = findMax max maxPos (curPos+1) xs
findMax max pos _ [] = (max:pos:[])

euler_p014_not_efficient = findMax 0 0 0 sequencesLengths

-- a more efficient way taken from: http://www.haskell.org/haskellwiki/Euler_problems/11_to_20

euler_p014 = j 1000000 where   
    f :: Int -> Integer -> Int   
    f k 1 = k   
    f k n = f (k+1) $ if even n then div n 2 else 3*n + 1   
    g x y = if snd x < snd y then y else x   
    h x n = g x (n, f 1 n)   
    j n = fst $ foldl' h (1,1) [2..n-1]