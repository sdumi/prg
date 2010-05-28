#!/bin/env python
"""
001.
  compute the greatest common divisor and least common multiple of n
numbers
  INPUT:
    read the numbers from stdin (separated by whitespace)
    lines are read until EOF is encountered.
  OUTPUT:
    a 3-tuple: 
    first element: a tuple containing the numbers
    second element: the gcd
    third element: the lcm
    ex:
    ((4 6 8), 2, 24)
"""

import sys

def gcd(a, b):
    """
    we will use the euclidean algorithm
    """
    print a, b
    if a == 0:
        return b
    if b == 0:
        return a
    if a == 1 or b == 1:
        return 1
    # make sure that a >= b:
    (a, b) = (b, a) if (a < b) else (a, b)
    return gcd (a-b, b)

def lcm(a, b):
    return (a*b)/gcd(a,b)

f = sys.stdin
lines = f.readlines()
for line in lines:
    numbers = tuple(map(int, line.split(' ')))
    d = reduce(gcd, numbers)
    m = reduce(lcm, numbers)
    res = (numbers, d, m)
    print res


