from random import randrange
def shuffle(items):
    """
    Durstenfeld shuffling algorithm (newer version of Fisher-Yates)
    """
    n = len(items)
    while n > 1:
        k = randrange(n) # 0..n-1
        n = n - 1
        items[k], items[n] = items[n], items[k]
    return items

shuffle(range(100))
