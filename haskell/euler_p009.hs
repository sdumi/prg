-- http://projecteuler.net/index.php?section=problems&id=9
-- A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,
-- a^(2) + b^(2) = c^(2)

-- For example, 3^(2) + 4^(2) = 9 + 16 = 25 = 5^(2).

-- There exists exactly one Pythagorean triplet for which a + b + c = 1000.
-- Find the product abc.
euler_p009 = [(a*b*c:a:b:c)|a<-[1..1000], b<-[1..1000],c<-[1000-a-b], (a<b)&&(b<c)&&((a+b+c)==1000)&&(a*a+b*b==c*c)]
