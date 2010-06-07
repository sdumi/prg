#!/bin/env ksh

DELAY=1 
COMM1='act-user::USER05:::Geheim005;'
COMM2='rtrv-hdr;'                     
COMM3='canc-user;'                     
logfile=/dev/null

telnet localhost 3083  |&
print -p $COMM1
sleep 1
echo "dumi"
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q
sleep 1
read -p a b c d e f g h i j k l m n o p
echo  $a $b $c $d $e $f $g $h $i $j $k $l $m $n $o $p $q

print -p $COMM2 
sleep $DELAY
print -p $COMM3 
sleep $DELAY

exit 0
