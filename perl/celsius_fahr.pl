#!/local/app/bin/perl -w

#A Celsius->Fahrenheit Converter

print "Please enter a Celsius degree > ";
chomp($cel = <STDIN>);

$fah = ($cel * 1.8) + 32;

print "The Fahrenheit equivalent of $cel degrees Celsius is $fah\n";
