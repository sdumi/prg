#!/bin/env python

import tempfile
import os
import sys
import getopt
import shutil
import stat

def getArgs(argv):
    try:
        opts, args = getopt.getopt(argv,
                                   "hf:i:s:",
                                   ["help", "file=", "input=", "sandbox="])
    except getopt.GetoptError:
        usage()
        sys.exit(1)
    fileToTest = ""
    inputFrom  = ""
    sandbox    = "/local/sandboxes/prog"
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit()
        elif opt in ("-f", "--file"):
            fileToTest = arg
        elif opt in ("-i", "--input"):
            inputFrom = arg
        elif opt in ("-s", "--sandbox"):
            sandbox = arg
    if fileToTest == "":
        usage()
        sys.exit(1)
    return (fileToTest, inputFrom, sandbox)

def usage():
    print sys.argv[0], " OPTIONS"
    print "OPTIONS:"
    print "  -h                 : display help and exit. OPTIONAL"
    print "  -f, --file=name    : python program to be run. MANDATORY"
    print "  -i, --input=name   : file to use as input instead of STDIN. OPTIONAL"
    print "  -s, --sandbox=name : sandbox to be used. OPTIONAL"
    print "                       default: /local/sandboxes/prog"

def createTempFile(directory):
    tempFile = tempfile.NamedTemporaryFile(dir=directory, delete=False)
    # we close the file: as we don't really want to write ourselves to it
    tempFile.close()
    return tempFile

def createAndCopyTempFile(origFile, directory):
    tempFile = createTempFile(directory)
    # copy the orig file to this temp file (which is already present in the sandbox directory)
    shutil.copyfile(origFile, tempFile.name)
    return tempFile

def main(argv):
    fileToTest, inputFrom, sandbox = getArgs(argv)
    # we will copy "fileToTest" to "sandbox/testarea/" but with a temporary name
    tempFileToTest = createAndCopyTempFile(fileToTest, (sandbox+"/testarea"))
    tempInputFrom = ""
    if inputFrom != "":
        tempInputFrom = createAndCopyTempFile(inputFrom, (sandbox+"/testarea"))
    # we will want to write stuff to this bash script:
    tempBashScript = tempfile.NamedTemporaryFile(dir=(sandbox+"/testarea"), delete=False)
    os.chmod(tempBashScript.name, stat.S_IRWXU )
    tempBashScript.file.write("#!/bin/sh\n")
    line = "python " + tempFileToTest.name.replace(sandbox, "", 1)
    if inputFrom != "":
        line += " < " + tempInputFrom.name.replace(sandbox, "", 1)
    line += "\n"
    tempBashScript.file.write(line)
    tempBashScript.close()

    commandToRun = "fakechroot -- chroot " + sandbox + " " + tempBashScript.name.replace(sandbox, "", 1)
    # run the command
    os.system(commandToRun)

    # delete the temporary files
    os.unlink(tempFileToTest.name)
    os.unlink(tempInputFrom.name)
    os.unlink(tempBashScript.name)

if __name__ == "__main__":
    main(sys.argv[1:])
