#!/local/app/bin/perl -w




@nums = (3, 4, 5);
$nums[4] = 7; #(3, 4, 5, undef, 7) expected

$, = "\n";
print @nums;
