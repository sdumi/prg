-- pattern matching: add
sumList (x:xs) = x + sumList xs
sumList []     = 0