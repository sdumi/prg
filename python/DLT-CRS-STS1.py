#!/usr/bin/env python

# #!c:\Python25\python.exe
"""
A script used to send multiple TL1 commands to a TL1 process using the telnet interface
"""
"""
An echo client that allows the user to send multiple lines to the server.
Entering 'quit' will exit the client
"""
import select
import socket
import sys
import time
import datetime
import os
import getopt

####################################################### GLOBALS ########################################
host = '127.0.0.1'
port = 3083 # TL1 port
size = 1024
###########################################################################################

###############################################################################################################
def usage():
    return
###############################################################################################################
def processArguments(argv):
    try:
        opts, args=getopt.getopt(argv, "hg:d", ["help", "grammar="])
    except getopt.GetopError:
        usage()
        sys.exit(2)
    for opt, arg in opts:
        if opt in ("-h", "--help"):
            usage()
            sys.exit()
        elif opt in ("-g", "--grammar"):
            grammar = arg
        el
    return

###############################################################################################################
def connect(host, port):
    #connect to server
    s_conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s_conn.connect((host, port))
    #setup the input list: socket and keyboard
    input = [s_conn]
    #read any hello messages from the server:
    data = s_conn.recv(size)
    # TL1 authentification phase:
    # we will send the command: "ACT-USER::EML001:::Geheim000;" 
    # to the TL1 server
    #sys.stdout.write("trying to authenthicate to TL1 server")
    tl1_auth_cmd = "ACT-USER::EML001:::Geheim000;"
    s_conn.send(tl1_auth_cmd)
    #read the response from the server:
    data = s_conn.recv(size)
    # sys.stdout.write("--> ")    
    #sys.stdout.write(data)
    # sys.stdout.write('\n% ')
    return input

###############################################################################################################
def increaseCounter(data, counter):
    start=0
    end=len(data)
    # search for COMPLDs
    start = data.find("COMPLD", 0, end)
    while(start != -1):
        counter = counter + 1
        start   = data.find("COMPLD", start + 1, end)
        #print start
        #print data
    # search for DENYs
    start = data.find("DENY", 0, end)
    while(start != -1):
        counter = counter + 1
        start   = data.find("DENY", start + 1, end)
    #print counter
    return counter

####################################################### CUSTOM LOOP ###########################################
# in this loop we will issue individual RTRV-STS1 for some STSs
def launchCommands(input, times):
    #WARNING... not nice
    s_conn = input[0]
    counter = 0
    for l in range (1, times + 1):
        for i in range (1, 11):
            for j in range (1, 65):
                for k in range (1, 4):
                    sts_pos1 = `2*l-1`+ "-" + `i` + "-" + `j` + "-" + `k`
                    sts_pos2 = `2*l`  + "-" + `i` + "-" + `j` + "-" + `k`
                    cmd = "DLT-CRS-STS1::OC192STS1-1-1-" + sts_pos1 +", OC192STS1-1-1-" + sts_pos2 + ";"
                    #sys.stdout.write("--> " + cmd)
                    s_conn.send(cmd)
                    # read something from the sockets:
                inputready, outputready, exceptready = select.select(input, [], [])
                for s in inputready:
                    if s == s_conn:
                        data = s_conn.recv(size)
                        counter = increaseCounter(data, counter)
                        #sys.stdout.write(data)
    return counter
###############################################################################################################
progress_chars = ["\\", "|", "/", "-"]
current_char = 0
def printProgress(counter):
#     global current_char
#     global progress_chars
#     if ((counter % 100) == 0):
#         sys.stdout.write(chr(8))
#         sys.stdout.write(progress_chars[current_char])
#         sys.stdout.flush()
#         current_char = (current_char + 1) % 4
    if ((counter % 500) == 0):
#        sys.stdout.write(chr(8))
        sys.stdout.write(".")
#        sys.stdout.write(progress_chars[current_char])
        sys.stdout.flush()

####################################################### MAIN LOOP #############################################
#now ready to accept other input from telnet user:
def mainLoop(input, counter, totalCmds):
    #WARNING... not nice
    s_conn = input[0]
    running = 1
    while running:
        #print counter
        if (counter == totalCmds):
            running = 0
            break
        inputready, outputready, exceptready = select.select(input, [], [])
        for s in inputready:
            if s == s_conn:
                #sys.stdout.write('# ')
                # read the socket:
                data = s_conn.recv(size)
                counter = increaseCounter(data, counter)
                #if (len(data) > 0):
                #sys.stdout.write("<-- ")
                    #sys.stdout.write(data)
                #sys.stdout.write('% ')
                #print ("dumi")
        printProgress(counter)
        if (counter == totalCmds):
            running = 0
            print "."
            return counter
                #if (len(data) > 0):
                #sys.stdout.write("<-- ")
                    #sys.stdout.write(data)
                #sys.stdout.write('% ')
                #print ("dumi")
#s_conn.close()
###############################################################################################################
def main(argv):
    processArguments(argv)
    TL1 = 'TL1'
    for a in range(1, 2):
        print "\n ---------------------------------------------------------- \n"
        print "ITERATION: ", a
        print "\n ---------------------------------------------------------- \n"
        for i in range(32, 33):
            print "\n --------------------------------------"
            print "STARTING STEP", i
            print datetime.datetime.now(), "\n"
            print "TL1 pid:"
            pidTL1 = os.system("pidof " + TL1)
        #print "TL1 pid: ", pidTL1
            if pidTL1 == 256:
                print "no TL1 process found"
                print "Sleeping for 10 minutes..."
                time.sleep(600)
                break
            input     = connect(host, port)
            counter   = launchCommands(input, i)
            totalCmds = i*10*64*3
            print "After launchCommands:"
            print "counter = ", counter, " totalCmds = ", totalCmds
            counter = mainLoop(input, counter, totalCmds)
            print "After mainLoop:"
            print "counter = ", counter, " totalCmds = ", totalCmds
            print "FINISHED STEP", i
            print datetime.datetime.now(), "\n"
            print "--------------------------------------"
            input[0].close()
            print "Killing the TL1 process..."
            os.system("killall -9 " + TL1)
            print "Sleeping for 10 seconds..."
            time.sleep(10)

if __name__ == "__main__":
    main(sys.argv[1:])

