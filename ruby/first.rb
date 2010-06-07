l = ["ceva", "altceva"]

l.each {|m| print m, " "}
print "\n"
def fib(n)
	return (n>1)?fib(n-2) + fib(n-1):n
end

print fib(6)
print fib(30)
