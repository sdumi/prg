#!/local/dev/bin/perl

set randomkey=`perl -e 'for (1..4) { 
    srand(time+$$+$seed); 
    printf("%4.5x", ($seed = int(rand(65536))));
  } 
  print "\n";'`;

  xauth add "`hostname`/unix:0" . $randomkey;
  xauth add "`hostname`:0" . $randomkey;

