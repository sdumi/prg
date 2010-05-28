#!/local/app/bin/perl -w

for (keys %main::) {
    print $_, " => ", $main::{$_}, "\n";
}
$abc = 2;
