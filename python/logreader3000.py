#!/usr/bin/env python2.6
import sys
import subprocess
from multiprocessing import Process, Queue

def say(line):
    say = '(SayText "%s")' % line
    echo = subprocess.Popen(['echo', say], stdout=subprocess.PIPE)
    subprocess.call(['festival'], stdin=echo.stdout)

def listen_to_lines(queue):
    line = 'I am Log Reader 3000.  The world is beautiful.'
    while True:
        while not queue.empty():
            line = queue.get()
        say(line)

queue = Queue()
p = Process(target=listen_to_lines, args=(queue,))
p.start()

while True:
    line = sys.stdin.readline()
    sys.stdout.write(line)
    queue.put(line)
