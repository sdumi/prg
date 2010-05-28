#!/bin/env perl

use Net::Telnet ();

for ( $i = 0; $i < 100; $i++ ) 
{
    $t = new Net::Telnet ( Timeout => 10,
			   Telnetmode => 0,
			   Prompt => $prompt);
    $t->open(Host => $hostname,
	     Port => 3083);
    @connections_array[$i] = $t;
#    $t->print("act-user::".$username.":::".$passwd.";");
    $t->print("act-user::DUMITEST:::PAROLA;");
}
for ($count = 10; $count >= 1; $count--) {
print "$count ";
}
print "Blastoff.\n"; 
