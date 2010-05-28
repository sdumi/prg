#!/local/app/bin/perl -w

@colors = ("red", "orange", "green", "blue");

$colors[0] = "yellow";

#foreach $color (@colors) {
#    print "$color ";
#}
#print "\n";
print "@colors\n";
@unix = ("FreeBSD", "Linux");
@os   = ("MacOS", ("Windows NT", "Windows Vista"), @unix);
print "@os\n";

