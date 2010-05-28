#!/local/app/bin/perl -w

print "Please input the width of the base (1-50) > ";
chomp($input = <STDIN>);
if ($input < 1 or $input > 50) {
    die "Input must be in the range (1..50)!\n";
}
for ($trend = 0, $i = $input; $i <= $input; ($trend)?($i+=2):($i-=2)) {
    if ($i == 1 or $i == 2) {
        $trend = 1;
    }
    print " " x (($input - $i)/2) . "*" x $i . "\n";
}
