-- Write a function lastButOne, that returns the element before the last.

lastButOne xs = if null xs 
                then xs
                else if null (tail xs)
                     then xs
                     else if null (tail (tail xs))
                          then [head xs]
                          else lastButOne (tail xs)
