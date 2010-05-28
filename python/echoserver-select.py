#!/usr/bin/env python
# #!c:\Python25\python.exe

"""
An echo server that uses select to handle multiple clients at a time.
Entering any line of input at the terminal will exit the server.
"""

import select
import socket
import sys

host = ''
port = 50001
backlog = 5
size = 1024
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.bind((host, port))
server.listen(backlog)
# stupid Windows... select.select() accepts only socket objects on Windows
#input = [server]
# hehe... we're on linux now
input = [server, sys.stdin]
running = 1
while running:
	inputready, outputready, exceptready = select.select(input, [], [])
	for s in inputready:
		if s == server:
			#handle the server socket
			client, address = server.accept()
			input.append(client)
			client.send("hello my friend")
			print("someone just connected to us...")
		elif s == sys.stdin:
			#handle standard input
			junk = sys.stdin.readline()
			running = 0
		else:
			#handle all other sockets
			data = s.recv(size)
			if data:
				s.send(data.upper())
				print(data)
				if data.rstrip('\n') == "close server":
					running = 0
			else:
				s.close()
				input.remove(s)
server.close()
