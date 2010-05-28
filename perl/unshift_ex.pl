#!/local/app/bin/perl -w

@alpha1 = ("a", "b", "c");
@alpha2 = ("d", "e", "f");

unshift @alpha2, @alpha1;
$, = " "; # Prints a space in between elements
print @alpha2;
