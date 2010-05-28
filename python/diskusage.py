#!/usr/bin/env python

import sys
import os

totalSize = 0
#for root, dirs, files in os.walk(os.getcwd()):
d = {}
d['/local/Alcatool'] = {}
currentDir = d
for root, dirs, files in os.walk('/local/Alcatool'):
    #print "root = ", root
    #print "dirs = ", dirs
#    print "files = ", files
    size = 0
    for file in files:
        try:
            size += os.path.getsize(os.path.join(root, file))
        except OSError:
            print "error trying to get size of: ", os.path.join(root, file)
    #print "size of files from dir: ", root, " is: ", size
    totalSize += size
    currentDir = d[root]
    currentDir['size'] = size
    currentDir['dirs'] = [os.path.join(root, d1) for d1 in dirs]
    currentDir['root'] = root
    for d1 in dirs:
        d[os.path.join(root, d1)] = {}
a = [x for x in d.iteritems()]
a = d.keys()
a.sort()
#print a
#for idx in a:
#    print d[idx]['size'], "\t\t", idx

def consolidateSize(sizes):
    if sizes:
        if sizes['dirs']:
            for x in sizes['dirs']:
                sizes['size'] += consolidateSize(d[x])
        return sizes['size']
    return 0
#print d
consolidateSize(d['/local/Alcatool'])
for idx in a:
    print d[idx]['size'], "\t\t", idx

#print os.stat('/home/dsipos/prg/python/diskusage.py')
#print os.path.getsize('/home/dsipos/prg/python/diskusage.py')
#print os.path.getsize('/home/dsipos/prg/python/')
print "total size of /local/Alcatool is: ", totalSize

