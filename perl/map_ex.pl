#!/local/app/bin/perl -w

@names = ('ALICE', 'tOM', 'JaSOn', 'peter');
print join(', ', map{ucfirst(lc($_))} @names), "\n";
