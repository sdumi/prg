#!/usr/bin/env python

# #!c:\Python25\python.exe
"""
An echo client that allows the user to send multiple lines to the server.
Entering a blank line will exit the client.
"""

import socket
import sys

host = '127.0.0.1'
port = 50000
size = 1024
print("dumi")
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect((host, port))
#read the hello message from the server:
data = s.recv(size)
sys.stdout.write("--> ")    
sys.stdout.write(data)
sys.stdout.write('\n% ')

while 1:
    #read from keyboard
    line = sys.stdin.readline()
    sys.stdout.write("<-- ")
    sys.stdout.write(line)
    if line.rstrip('\n') == "quit":
        print ("umm... I think we should quit now")
        break
    s.send(line)
#    sys.stdout.write('# we just sent: ')
    sys.stdout.write("--> ")    
    data = s.recv(size)
    sys.stdout.write(data)
    sys.stdout.write('% ')
s.close()
