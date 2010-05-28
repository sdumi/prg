#!/bin/env python

def cross(A, B):
    return [a+b for a in A for b in B]

rows = 'ABCDEFGHI'
cols = '123456789'
digits = '123456789'
squares = cross(rows, cols)
#print squares
unitlist = ([cross(rows, c) for c in cols] +
            [cross(r, cols) for r in rows] +
            [cross(rs, cs) for rs in ('ABC', 'DEF', 'GHI') for cs in ('123', '456', '789')])
#print unitlist


units = dict((s, [u for u in unitlist if s in u]) 
             for s in squares)
peers = dict((s, set(s2 for u in units[s] for s2 in u if s2 != s))
             for s in squares)
def parse_grid(grid):
    "Given a string of 81 digits (or . or 0 or -), return a dict of {cell:values}"
    grid = [c for c in grid if c in '0.-123456789']
    values = dict((s, digits) for s in squares) ## To start, every square can be any digit
    for s,d in zip(squares, grid):
        if d in digits and not assign(values, s, d):
	    return False
    return values

def assign(values, s, d):
    "Eliminate all the other values (except d) from values[s] and propagate."
    if all(eliminate(values, s, d2) for d2 in values[s] if d2 != d):
        return values
    else:
        return False

def eliminate(values, s, d):
    "Eliminate d from values[s]; propagate when values or places <= 2."
    if d not in values[s]:
        return values ## Already eliminated
    values[s] = values[s].replace(d,'')
    if len(values[s]) == 0:
	return False ## Contradiction: removed last value
    elif len(values[s]) == 1:
	## If there is only one value (d2) left in square, remove it from peers
        d2, = values[s]
        if not all(eliminate(values, s2, d2) for s2 in peers[s]):
            return False
    ## Now check the places where d appears in the units of s
    for u in units[s]:
	dplaces = [s for s in u if d in values[s]]
	if len(dplaces) == 0:
	    return False
	elif len(dplaces) == 1:
	    # d can only be in one place in unit; assign it there
            if not assign(values, dplaces[0], d):
                return False
    return values

def printboard(values):
    "Used for debugging."
    width = 1+max(len(values[s]) for s in squares)
    line = '\n' + '+'.join(['-'*(width*3)]*3)
    for r in rows:
        print ''.join(values[r+c].center(width)+(c in '36' and '|' or '')
                      for c in cols) + (r in 'CF' and line or '')
    print
def search(values):
    "Using depth-first search and propagation, try all possible values."
    if values is False:
        return False ## Failed earlier
    if all(len(values[s]) == 1 for s in squares): 
        return values ## Solved!
    ## Chose the unfilled square s with the fewest possibilities
    _,s = min((len(values[s]), s) for s in squares if len(values[s]) > 1)
    return some(search(assign(values.copy(), s, d)) 
		for d in values[s])

grid = """
003020600
900305001
001806400
008102900
700000008
006708200
002609500
800203009
005010300"""

printboard(parse_grid(grid))

grid = '4.....8.5.3..........7......2.....6.....8.4......1.......6.3.7.5..2.....1.4......'
printboard(parse_grid(grid))
