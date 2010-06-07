#!/bin/sh
echo $1
for HOST in `cat`
do
  echo Connecting to $HOST...
  telnet $HOST 3083  </dev/tty
  #telnet $HOST 3083  < $1
done
