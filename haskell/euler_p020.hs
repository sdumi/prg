-- http://projecteuler.net/index.php?section=problems&id=20
-- n! means n × (n − 1) × ... × 3 × 2 × 1

-- Find the sum of the digits in the number 100!
import Data.Char
euler_p020 = sum (map digitToInt (show (foldl (*) 1 [1..100])))