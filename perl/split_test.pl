#!/local/app/bin/perl -w

$_ = 'Piper       PA-28  Archer           OO-ROB
Antwerp';

@details = split /\s+/, $_;
foreach (@details) {
    print "$_\n";
}
@chars = split //, $details[0];
foreach $char (@chars) {
    print "$char !\n";
}


open (AAA, "test_m_n.txt") || die "Cannot open file";
@file_array = <AAA>;
close AAA;

foreach $line (@file_array) {
    print "$line \n";
    @splitter = split /,/ , $line;
    
}
