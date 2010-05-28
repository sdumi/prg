#!/usr/bin/env perl
# testing Hash of Arrays

# variant 1
while ( <> )
{
    next unless s/^(.*?):\s*//;
    $HoA1{$1} = [ split ];
}
#for $family ( keys %HoA1 ) {
#    print "$family: @{ $HoA1{$family} }\n";
#}

for $family ( keys %HoA1 ) {
    print "$family: ";
    for $i ( 0 .. $#{ $HoA1{$family} } ) {
        print " $i = $HoA1{$family}[$i]";
    }
    print "\n";
}

# variant 2
#while ( $line = <> )
#{
#    ($who, $rest) = split /:\s*/, $line, 2;
#    @fields = split ' ', $rest;
#    $HoA2{$who} = [ @fields ]
#}
