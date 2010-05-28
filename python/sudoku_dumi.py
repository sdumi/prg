#!/bin/env python
import sys
import getopt
import string

def usage():
    print sys.argv[0], " [options]"
    print "options:"
    print "  -h               :display help and exit"
    print "  -f filename      :use filename as input, otherwise use stdin"
    print "  --file=filename  :see -f"

def zeroes_old(*shape):
    # does the same thing as zeroes(x, y)
    # except that it can create a matrix with more than 2 dimensions
    if len(shape) == 0:
        return 0
    car = shape[0]
    cdr = shape[1:]
    return [zeroes(*cdr) for i in range(car)]

def zeroes(x, y):
    return [ [0 for j in range(0,y)] for i in range(0, x)]

def get_sudoku(fname=""):
    f = sys.stdin if (fname == "") else file(fname)
    file_content = f.readlines()
    mx = zeroes(9,9)
    i = 0
    j = 0
    for line in file_content:
        j = 0
        # iterate over all chars in a line:
        # we'll try to ignore the whitespaces
        for number in line:
            if number not in string.whitespace :
                mx[i][j] = number
                j = j + 1
        i = i + 1
    return mx

def print_mx(mx):
    i = 0
    for line in mx:
        str = ""
        j = 0
        for number in line:
            str = str + number
            str = str + " "
            j = j + 1
            if (j % 3 == 0):
                str = str + "  "
        print str
        i = i + 1
        if (i % 3 == 0):
            print ""

def main(argv):
    # reading the arguments:
    try:
        opts, args = getopt.getopt(argv, "hf:", ["help", "file="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)
    fname = ""
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit()
        elif opt in ("-f", "--file"):
            fname = arg
    print_mx(get_sudoku(fname))

if __name__ == "__main__":
    main(sys.argv[1:])

