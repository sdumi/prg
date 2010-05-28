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

####################################################### INITIAL SETUP ########################################
host = '127.0.0.1'
port = 3083 # TL1 port
size = 1024

#connect to server
s_conn = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s_conn.connect((host, port))

#setup the input list: socket and keyboard
input = [s_conn, sys.stdin]

#read any hello messages from the server:
data = s_conn.recv(size)
# sys.stdout.write("--> ")    
#sys.stdout.write(data)

# TL1 authentification phase:
# we will send the command: "ACT-USER::EML001:::Geheim000;" 
# to the TL1 server
sys.stdout.write("trying to authenthicate to TL1 server")
tl1_auth_cmd = "ACT-USER::EML001:::Geheim000;"
s_conn.send(tl1_auth_cmd)

#read the response from the server:
data = s_conn.recv(size)
# sys.stdout.write("--> ")    
sys.stdout.write(data)
# sys.stdout.write('\n% ')
###############################################################################################################

####################################################### CUSTOM LOOP ###########################################
# in this loop we will issue individual RTRV-STS1 for some STSs

for i in range (1, 65):
    for j in range (1, 4):
        cmd = "RTRV-STS1::OC192STS1-1-1-1-1-" + `i` + "-" + `j` + ";"
        sys.stdout.write("--> " + cmd)
        s_conn.send(cmd)

    # read something from the sockets:
    inputready, outputready, exceptready = select.select(input, [], [])
    for s in inputready:
        if s == s_conn:
            data = s_conn.recv(size)
            sys.stdout.write(data)
        
###############################################################################################################


####################################################### MAIN LOOP #############################################
#now ready to accept other input from telnet user:
running = 1
while running:
    inputready, outputready, exceptready = select.select(input, [], [])
    for s in inputready:
        if s == s_conn:
            #sys.stdout.write('# ')
            # read the socket:
            data = s_conn.recv(size)
            if (len(data) > 0):
                #sys.stdout.write("<-- ")
                sys.stdout.write(data)
                #sys.stdout.write('% ')
                #print ("dumi")
        if s == sys.stdin:
            sys.stdout.write('# ')
            #read from keyboard
            line = sys.stdin.readline()
            sys.stdout.write("--> ")
            sys.stdout.write(line)
            if line.rstrip('\n') == "quit":
                print ("umm... I think we should quit now")
                running = 0
            s_conn.send(line)
            #    sys.stdout.write('# we just sent: ')
            sys.stdout.write('% ')
s_conn.close()
###############################################################################################################
