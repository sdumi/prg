#!/bin/env python
import sys
import getopt
import zlib
import base64
from StringIO import StringIO
from pyPdf import PdfFileReader, PdfFileWriter


__version__ = "0.0.1"
__license__ = "GPL 3"
__author__  = "Dumitru Sipos"
__date__    = "2010-11-04"

# the empty A4 page was taken from pdfnup (by Dinu Gherman):
#  http://nullege.com/codes/show/src%40p%40d%40pdfnup-0.4.1%40pdfnup.py/31/pyPdf.PdfFileReader/python
# one empty A4 page as base64-encoded zipped PDF file
_oneA4PdfZip64 = """\
eJyVVV1z2joQfWeG/7CTDjcwbfA3mLY3MwFCyrRpUyDpbUOmI2wB7hiJWnKT9KF/oH3re39rVzI2DrQPNzMO8mp1ztmjlVy76A+OrKZTrdR+/vj+C0Z0zRP5iszgjDKaEElDwBQIeZCuKJOwlHL91DBub2+bic6NyawZ8BUCwGGXiCgYcCbF4VMIYiKEWtyPAhlxRpJ7qFYsMIHPPqn0yZKCkISFJAlhrlZBWKRWK8+fgzGwwMYFIzg+rlYoCzcrDwdWmWByv6aWokV8e4uvIy9o/IXKKCAZICqkOm6UJsA4ZQEPI7YA413ETpiI8oCafE1WVElR43E6k8gGhuZUkYl+1Zg7Ii/Igj7QqQIo0dlK1JHdonuIRZUbbVW64jinYUS6/A6uwcR39Xgdr2m3vRYOfddq+n7HhxuVe0EStU+tfO2ICp4mARWgDVU6rXzuIuHBmEqENVCerobeSfU7XKGybjHqFaMh3Og6EZhLbA8txpgkhGmCzVxmiq5ux5SRW3akRySJ+QJNcbem9PNeG3EuM0vepDKOGNbgF9IR+5yHyHIp6GvOaB4U29IzFTnHrhCvLGTI5hxVeLkKRXqSyiVPoE4YZ/crnoqGAu0llKjt6qvi67Zp+mbH9i3PdCxbJ7yk97c8CQXUGxuPwzSgiLM9W387RI1Ni32igYR6ysSaBtE8oqGemEQypios1SBs7FXU2m02gSW1tsau1X7IhNK8z1LVDFpzhHqvwdFn7ebhDoo9nnaZZ4yAZIVE7R0ioSc25ziKJVqAfXYy7g2HvteneL70ng1iNDJ7zZhfUbaQS2iZmjdHOSPrt0vz9N/BE/Ny+sKJDq74+9Vn4/xx9+qD88/V0G043WdPhLh8vzo8mp2dHsiDyYeGfPTu47dj1J7DPCzELxdS9Fi14pfbILPJ3JpSJJZ9uUvovFoxoYP/ij9oeZ7jwbyIWRZarGdYEbPNzl7Madt7sZa7n9f29/E6HXc3ZmFwL+aYJQ6ZkCimSVbxsI8eQK30MVj8+WNwdISXF3YINutfW1pBXdfZ1DHNqe26/eOpbTvx1PbaU7ttv8WBNTUtGx8HH6v2XwP+V/YNqF1F0eoEe8Wth1cHuPnbOPpKobPpJ5LIbLMsx1PfvdrpG7z6fgMis+cW
"""
_oneA4Pdf = zlib.decompress(base64.decodestring(_oneA4PdfZip64))
	  

def getArgs(argv):
    try:
        opts, args = getopt.getopt(argv,
                                   "hf:o:",
                                   ["help", "file=", "output="])
    except getopt.GetoptError:
        usage()
        sys.exit(1)
    inputFrom  = ""
    output     = ""
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit()
        elif opt in ("-f", "--file"):
            fileInput = arg
        elif opt in ("-o", "--output"):
            fileOutput = arg
    if (fileInput == "") or (fileOutput == ""): 
        usage()
        sys.exit(1)
    return (fileInput, fileOutput)

def usage():
    print sys.argv[0], " OPTIONS"
    print "OPTIONS:"
    print "  -h                 : display help and exit. OPTIONAL"
    print "  -f, --file=name    : PDF input file. MANDATORY"
    print "  -o, --ouput=name   : outpuf file. MANDATORY"

def getPageOrEmpty(input, page):
    pages = input.getNumPages()
    if page < pages:
        return input.getPage(page)
    else:
        # create empty page
        buf = StringIO()
        buf.write(_oneA4Pdf)
        emptyReader = PdfFileReader(buf)
        return emptyReader.getPage(0)
        
def main(argv):
    inputFile, outputFile = getArgs(argv)
    input=PdfFileReader(file(inputFile, "rb"))
    output=PdfFileWriter()

    pages = input.getNumPages()
    if pages % 4 != 0:
        pages += 4 - (pages % 4)

    # create an A4 file  (4 pages in the right order):
    for i in range (0, pages / 4):
        # first add the last page
        lastPage = pages - (i * 2) - 1
        output.addPage(getPageOrEmpty(input, lastPage ))
        # add the first page:
        firstPage = i * 2
        output.addPage(getPageOrEmpty(input, firstPage))
        # add the second page:
        output.addPage(getPageOrEmpty(input, firstPage + 1))
        # add the page before the last one:
        output.addPage(getPageOrEmpty(input, lastPage - 1))
    
                       
    # output.addPage(input.getPage(11))
    # output.addPage(input.getPage(0))
    # output.addPage(input.getPage(1))
    # output.addPage(input.getPage(10))
    # output.addPage(input.getPage(9))
    # output.addPage(input.getPage(2))
    # output.addPage(input.getPage(3))
    # output.addPage(input.getPage(8))
    # output.addPage(input.getPage(7))
    # output.addPage(input.getPage(4))
    # output.addPage(input.getPage(5))
    # output.addPage(input.getPage(6))
    
    outputStream=file(outputFile, "wb")
    output.write(outputStream)
    outputStream.close()
    
if __name__ == "__main__":
    main(sys.argv[1:])
