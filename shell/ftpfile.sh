#!/bin/sh
# Usage:
# ftpfile machine file
# set -x
SOURCE=$1
FILE=$2
BFILE=`basename $FILE`
ftp -n $SOURCE <<EndFTP
ascii
user anonymous $USER@`hostname`
get $FILE /tmp/$BFILE
EndFTP
