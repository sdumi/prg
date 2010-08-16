def isPrime(n):
    """
      tests is a number n is prime or not. very naive implementation.
    """
    for i in range (2, n/2+1):
        if n % i == 0:
            return False
    return True

def primes(n):
    """
      returns a list with the first n prime numbers. very naive implementation
    """
    result = []
    i = 2
    while n > 0:
        if isPrime(i):
            result += [i]
            n -= 1
        i += 1
    return result

        
