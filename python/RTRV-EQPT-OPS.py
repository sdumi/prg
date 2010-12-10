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
    # we will send the command: "ACT-USER::EML001:::Geheim005;" 
    # to the TL1 server
    #sys.stdout.write("trying to authenthicate to TL1 server")
    tl1_auth_cmd = "ACT-USER::EML001:::Geheim005;"
    s_conn.send(tl1_auth_cmd)
    for i in range (1, 3):
        inputready, outputready, exceptready = select.select(input, [], [])
        for s in inputready:
            if s == s_conn:
                #sys.stdout.write('# ')
                # read the socket:
                data = s_conn.recv(size)
    return input

###############################################################################################################
def increaseCounter(data, counter, cmd):
    start=0
    end=len(data)
#    print cmd
#    print data
    if (data.find(";", 0, end) == -1):
#        print "11"
        return counter
    # search for COMPLDs
    start = data.find(cmd, 0, end)
 #   print start
    while(start != -1):
        counter = counter + 1
        start   = data.find(cmd, start + 1, end)
    # search for DENYs
    start = data.find("DENY", 0, end)
 #   print start
    while(start != -1):
 #       counter = counter + 1
        start   = data.find("DENY", start + 1, end)
    #print counter
    return counter

####################################################### CUSTOM LOOP ###########################################
# in this loop we will issue individual RTRV-STS1 for some STSs
def launchCommand(input, times, cmd):
    s_conn = input[0]
    counter = 0
    #cmd = "RTRV-STS1::ALL;"
    cmd = cmd + ";"
    s_conn.send(cmd)
    return counter
###############################################################################################################
progress_chars = ["\\", "|", "/", "-"]
current_char = 0
def printProgress(counter):
    if ((counter % 500) == 0):
        sys.stdout.write(".")
        sys.stdout.flush()

####################################################### MAIN LOOP #############################################
#now ready to accept other input from telnet user:
def mainLoop(input, counter, totalCmds, cmd):
    s_conn = input[0]
    running = 1
    while running:
        if (counter == totalCmds):
            running = 0
            break
        inputready, outputready, exceptready = select.select(input, [], [])
        for s in inputready:
            if s == s_conn:
                # read the socket:
                data = s_conn.recv(size)
                counter = increaseCounter(data, counter, cmd)
        if (counter >= totalCmds):
            running = 0
            return counter

###############################################################################################################
def main(argv):
    processArguments(argv)
    TL1 = 'TL1'
    input     = connect(host, port)
    print "TL1 pid:"
    pidTL1 = os.system("pidof " + TL1)
        #print "TL1 pid: ", pidTL1
    if pidTL1 == 256:
        print "no TL1 process found"
        return
    i = 1
    commands = []
#     for x in range (1, 7):
#         for y in range (1, 11):
# #            tmpCmd = "ent-ffp-oc192::FFPOC192-1-1-"+`x*2`+"-"+`y`+"::::PTYPE=LINEAR,WKG=OC192-1-1-"+`x*2-1`+"-"+`y`+",PROTN=OC192-1-1-"+`x*2`+"-"+`y`
#             tmpCmd = "rls-protnsw-oc192::FFPOC192-1-1-"+`x*2`+"-"+`y`
#             commands.append(tmpCmd)
# #ent-eqpt::XFP-1-1-1&&-16-1&&-10&XFP-1-1-33&&-48-1&&-10::::PROVISIONEDTYPE=SR111G1AU,CLNTSEL=OC192;

#     for a in range (1, 17):
#         for b in range (1, 11):
#             for c in range (1, 65):
#                 for d in range (1, 4):
#                     pos = `a`+"-"+`b`+"-"+`c`+"-"+`d`
#                     tmpCmd = "ED-STS1::OC192STS1-1-1-"+pos+":::::OOS,AINS-DEA"
#                     commands.append(tmpCmd)
#                     pos =  `a+32`+"-"+`b`+"-"+`c`+"-"+`d`
#                     tmpCmd = "ED-STS1::OC192STS1-1-1-"+pos+":::::OOS,AINS-DEA"
#                     commands.append(tmpCmd)
    commands.append("RTRV-EQPT::OPS-1-1")
    while (i<1000000000):
        print "\n--------------------------------------"
        print "STARTING STEP", i
        for cmd in commands:
            print "--------------"
            print "command: ", cmd
            starttime=datetime.datetime.now()
            print "START = ", starttime
            counter = launchCommand(input, i, cmd)
            mainLoop(input, counter, 1, cmd)
            endtime = datetime.datetime.now()
            print "END =    ", endtime
            print "----"
            print "delta time = ", endtime-starttime
            print "--------------"
        print "FINISHED STEP", i
        print "--------------------------------------"
#        print "Please press Enter when ready to do another STEP... a non empty line will terminate the script."
#         msg=sys.stdin.readline()
#         if len(msg) > 1:
#             print "we are done now: closing the connection..."
#             input[0].close
#             return
        i = i + 1

if __name__ == "__main__":
    main(sys.argv[1:])

