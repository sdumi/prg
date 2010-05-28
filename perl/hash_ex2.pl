#!/local/app/bin/perl -w

# Search for an element in a hash
# Generating 100 integers
$NUM = 100;
$MAXINT = 5000;     # 1 + the maximum integer generated
srand();        # initialize the randomize seed
print "Numbers Generated:\n(";
for $i (1 .. $NUM) {
    $valueToInsert = sprintf("%d", rand(1) * $MAXINT);
    $hash{$valueToInsert} = 0; # in fact, any values can be assigned here
    print $valueToInsert;
    print ", " unless ($i == $NUM);
}
print ")\n\n";
print "Please enter the number to search for >> ";
chomp($toSearch = <STDIN>);
# Hash search here
if (exists($hash{$toSearch})) {
    print "\"$toSearch\" found!\n";
} else {
    print "\"$toSearch\" not found!\n";
}
