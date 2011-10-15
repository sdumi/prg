#!/usr/bin/env python2.7
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
                                   "hf:o:g:b:a:s:c:",
                                   ["help", "file=", "output=", "groupsize=", "beforepad=", "afterpad=", "startpage=", "crop="])
    except getopt.GetoptError:
        usage()
        sys.exit(1)
    groupSize = 0
    beforePad = 0
    afterPad  = 0
    startPage = 0
    cropSize  = 0
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit()
        elif opt in ("-f", "--file"):
            fileInput = arg
        elif opt in ("-o", "--output"):
            fileOutput = arg
        elif opt in ("-g", "--groupsize"):
            groupSize = int(arg)
        elif opt in ("-b", "--beforepad"):
            beforePad = int(arg)
        elif opt in ("-a", "--afterpad"):
            afterPad = int(arg)
        elif opt in ("-s", "--startpage"):
            startPage = int(arg)
        elif opt in ("-c", "--crop"):
            cropSize = int(arg)
            
    if (fileInput == "") or (fileOutput == ""): 
        usage()
        sys.exit(1)
    return (fileInput, fileOutput, groupSize, beforePad, afterPad, startPage, cropSize)

def usage():
    print sys.argv[0], " OPTIONS"
    print "OPTIONS:"
    print "  -h                     : display help and exit. OPTIONAL"
    print "  -f, --file=name        : PDF input file. MANDATORY"
    print "  -o, --ouput=name       : outpuf file. MANDATORY"
    print "  -g, --groupsize=size   : number of pages in a group (rounded to the next multiple of 4). OPTIONAL"
    print "                           default: number of pages in input document"
    print "  -b, --beforepad=size   : number of blank pages to be inserted at the beginning of document.OPTIONAL"
    print "                           default: 0"
    print "  -a, --afterpad=size    : minimum number of blank pages to be inserted at the end of document. OPTIONAL"
    print "                           default: whatever needed to make the output pages a multiple of 4"
    print "  -s, --startpage=nr     : start page from input document. OPTIONAL"
    print "                           default: 0"
    print "  -c, --crop=nr          : how much to crop. OPTIONAL"
    print "                           default: 0"

def createEmptyPage():
    # create empty page
    buf = StringIO()
    buf.write(_oneA4Pdf)
    emptyReader = PdfFileReader(buf)
    return emptyReader.getPage(0)

def cropPage_L(page, crop):
    page.cropBox.lowerLeft=(crop, 0)
    return page

def cropPage_R(page, crop):
    page.cropBox.lowerRight=(page.cropBox.getLowerRight_x()-crop,0)
    return page

def processGroup(output, group, crop):
    if (not group):
        return
    if len(group) % 4 != 0:
        print "Something wrong happened: group size not multiple of 4:", len(group)
        sys.exit(1)
    pages = len(group)
    # create an A4 file  (4 pages in the right order):
    for i in range (0, pages / 4):
        # first add the last page
        lastPage = pages - (i * 2) - 1
        output.addPage(cropPage_L(group[lastPage], crop))
        # add the first page:
        firstPage = i * 2
        output.addPage(cropPage_R(group[firstPage], crop))
        # add the second page:
        output.addPage(cropPage_L(group[firstPage + 1], crop))
        # add the page before the last one:
        output.addPage(cropPage_R(group[lastPage - 1], crop))

def main(argv):
    inputFile, outputFile, groupSize, beforePad, afterPad, startPage, cropSize = getArgs(argv)
    print inputFile, outputFile, groupSize, beforePad, afterPad, startPage
    if groupSize % 4 != 0:
        groupSize += 4 - (groupSize % 4)
    print groupSize

    input=PdfFileReader(file(inputFile, "rb"))
    output=PdfFileWriter()

    # take pages from input document. add blank pages at the beginning or the end...
    emptyPage = createEmptyPage()
    inp = []
    for i in range(0, beforePad):
        inp.append(emptyPage)
    inp.extend([input.pages[x] for x in range(startPage, input.getNumPages())])

    extra = 0
    pages = len(inp) + afterPad
    if pages % 4 != 0:
        extra += 4 - (pages % 4)
    
    for i in range(0, afterPad + extra):
        inp.append(emptyPage)
    pages = len(inp)

    # now we have the pages in inp. split them in groups and process each group separately
    group = []
    for p in inp:
        group.append(p)
        if len(group) == groupSize:
            processGroup(output, group, cropSize)
            group = []
    processGroup(output, group, cropSize)
                           
    outputStream=file(outputFile, "wb")
    output.write(outputStream)
    outputStream.close()
    
if __name__ == "__main__":
    main(sys.argv[1:])
