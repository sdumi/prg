#!/local/app/bin/perl -w

sub sum (@) {
    # This subroutine takes a list of numbers as input
    # and returns the sum
    my $sum = 0;
    for my $tmp (@_) {
	$sum += $tmp;
    }
    return $sum;
}

#calculates 0+1+2+...+100 and prints the value
print sum(0 .. 100), "\n"; # must be 5050. seriously.
@nums = (0 .. 100);
$avg = sum(@nums)/@nums;
print "Avg : ", $avg;
