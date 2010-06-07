#!/bin/env ksh

#SSG_details is file from which script will read ip adress and uname/password
#to telnet.

SSG_detail=./telnetTest.txt

cat $SSG_detail | while read ssg_det ; do

   ssg_ip=`echo $ssg_det|awk '{print $1}'`
   ssg_port=`echo $ssg_det|awk '{print $2}'`


   echo " IP to telnet:" $ssg_ip
   echo " port:" $ssg_port

   sh  ./Call_Telnet.sh $ssg_ip $ssg_port

done


exit 0
