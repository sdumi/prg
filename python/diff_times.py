#!/bin/env python
import sys

f = sys.stdin
dates = f.readlines()
previous = 0
for line in dates:
    hour = int(line[0:2])
    minute = int(line[3:5])
    sec = int(line[6:8])
    usec = int(line[10:])
    
#    current = (sec + 60*minute + 60*60*hour)*1000 + usec
    current = (sec + 60*minute + 60*60*hour)
    delta = current - previous
    print line.strip(), "   ", delta
    previous = current
