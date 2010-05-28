#!/usr/bin/env perl
#use strict;
#Hash of Hash

%HoH = (
    flintstones => {
        husband   => "fred",
        pal       => "barney",
    },
    jetsons => {
        husband   => "george",
        wife      => "jane",
        "his boy" => "elroy",  # Key quotes needed.
    },
    simpsons => {
        husband   => "homer",
        wife      => "marge",
        kid       => "bart",
    },
);
$HoH{ mash } = {
    captain  => "pierce",
    major    => "burns",
    corporal => "radar",
};
my %newUnion = ('__F_Union_' => {'dummy'=> {'__F_Struct_' => {'empty' => '0'}}});

$HoH{gabi} = {
 '__F_Union_' => {
        'dummy'=> {
              '__F_Struct_' => {'empty' => '0'}}}
};

$HoH{mash} = {%newUnion};

for $family ( keys %HoH ) {
    print "$family: ";
    for $role ( keys %{ $HoH{$family} } ) {
         print "$role=$HoH{$family}{$role} ";
    }
    print "\n";
}
