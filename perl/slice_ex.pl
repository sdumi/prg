#!/local/app/bin/perl -w


@alpha = ('a' .. 'z');
@slice = @alpha[4, 10..15];

$, = " ";
print @slice;
