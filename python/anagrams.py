def sortuple(word) :
    letters = [l for l in word.strip()]
    letters.sort()
    return tuple(letters)

bytuple={}
pairs=[]

for w in open('/usr/share/dict/words') :
    w = w.strip("\n")
    tup = sortuple(w)
    if not "'" in tup :
        if tup in bytuple :
            pairs.append( (len(w),bytuple[tup],w) )
        else :
            bytuple[tup] = w

pairs.sort()
for tup in pairs[-1:-100:-1] :
    print("%2d %s %s" % tup)
