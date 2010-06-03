"""
This program will try to convert a 'mbox' mail file (Thunderbird) to 'maildir' (gnus).
receives as input the mbox file and the maildir directory
"""
import sys
import getopt

def writeMsgToFile(msg, file):
    f = open(file, 'w')
    f.write(msg)
    f.close()


def main(argv):
    # start by reading the arguments:
    try:
        opts, args = getopt.getopt(argv, "hf:o:s:", ["help", "file=", "outdir=", "start="])
    except getopt.GetoptError:
        usage()
        sys.exit(2)
    file = ""
    outdir = ""
    startIndex = 0
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit()
        elif opt in ("-f", "--file"):
            file = arg
        elif opt in ("-o", "--outdir"):
            outdir = arg
        elif opt in ("-s", "--start"):
            startIndex = int(arg)
    f = open (file)
    flines = f.readlines()
    nrMessages = 0
    linecount = len(flines)
    currMsg = ""
    for l in flines:
        if (l[0:5] == "From "):
            if (nrMessages > 0):
                path = outdir +"/" + str(startIndex + nrMessages)
                writeMsgToFile(currMsg, path)
            nrMessages += 1
            currMsg = l
        else:
            currMsg += l
    writeMsgToFile(currMsg, outdir + "/" + str(startIndex + nrMessages))
    print "we read: ", linecount, " lines"
    print "discovered: ", nrMessages, " messages"


if __name__ == "__main__":
    main(sys.argv[1:])
