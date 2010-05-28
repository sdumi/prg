#!/bin/env perl

sub checkIDN
{
# set idn 1 3 2 1
# avail iddd dontcare dontcare 2147483647 2147483647
#    my $idn = @_;
    my $idn = 1304;
    my $state = 'iddd';

    my $myExpr = qr((\d)(\d)(\d\d));
    $myExpr = qr((\d)(\d)(\d\d)(\d\d)) unless (length($idn) == 4);

    if ($idn =~ /$myExpr/)
    {
	my $r = $1;
	my $s = $2;
	my $b = $3;
	my $p = $4;
	$b = $1 if ( $b =~ /0(\d)/ );
	$p = $1 if ( $p =~ /0(\d)/ );
	$idn = "$r $s $b $p";
	print $idn;
	my @CmdList = ();
	push @CmdList, "set idn $idn";
	push @CmdList, "avail $state dontcare dontcare 2147483647 2147483647";
    } else {
	print "ERROR: The idn has the wrong format. IDN must be rsbbpp";
    }
}

checkIDN(130401);
