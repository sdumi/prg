##############################################################################
def word_to_struct(word):
#will return a dict containing the number of apparitions of each letter from 'word'
    result = {}
    for i in word:
        if result.has_key(i):
            result[i] = result[i] + 1
        else:
            result[i] = 1
    return result

##############################################################################
def read_dict(fname = "/local/src/OSPD3"):
#will read the file containing the words and store them in a dictionary (computes also the number of apparitions of each letter from a word)
    # read the file containing the words
    fileContent = file(fname).readlines()
    #    result = set([[i.rstrip('\n'):'dumi' for i in fileContent]])
    result = {}
    for i in fileContent:
        word = i.rstrip('\n')
        result[word] = word_to_struct(word)
    return result

##############################################################################
def possible(letters, dictionary):
#will find all the words from the 'dictionary' that can be made with the 'letters'
    # count the letters we have: 'DOOM' => D:1, O:2, M:1
    letDict = word_to_struct(letters)
    # how many letter do we have: it determines the maximum length of the words we search
    nrLetters = len(letters)
    result = []
    for word in dictionary.keys():
        if len(word) <= nrLetters:
            # OK... we have enough letters... see if we got the right ones:
            found = True
            for letter in dictionary[word].keys():
                if not (letDict.has_key(letter) and (dictionary[word][letter] >= letDict[letter])):
                    found = False
                    break
            if found:
                result.append(word)
    return result
##############################################################################
def gen_letter_score():
    result = {}
    result['A'] = 1
    result['B'] = 3
    result['C'] = 3
    result['D'] = 2
    result['E'] = 1
    result['F'] = 4
    result['G'] = 2
    result['H'] = 4
    result['I'] = 1
    result['J'] = 8
    result['K'] = 5
    result['L'] = 1
    result['M'] = 3
    result['N'] = 1
    result['O'] = 1
    result['P'] = 3
    result['Q'] = 10
    result['R'] = 1
    result['S'] = 1
    result['T'] = 1
    result['U'] = 1
    result['V'] = 4
    result['W'] = 4
    result['X'] = 8
    result['Y'] = 4
    result['Z'] = 10
    return result
##############################################################################
def word_score(word, score_table):
    result = 0
    for letter in word:
        result = result + score_table[letter]
    return result
##############################################################################
def word_score2(word):
    return word_score(word, gen_letter_score())
##############################################################################
letter_score_table = gen_letter_score()
##############################################################################
def compare_words(lhs, rhs):
    return (word_score2(lhs) < word_score2(rhs))
def myCmp(x, y):
    ws_lhs = word_score2(x)
    ws_rhs = word_score2(y)
    if ws_lhs == ws_rhs:
        if x == y:
            return 0
        elif x < y:
            return -1
        else:
            return 1
    else:
        return (ws_lhs - ws_rhs)

letter_score_table = gen_letter_score()
myDict = read_dict()


#print myDict.keys()
#print myDict.values()
poss = possible('DOMO', myDict)
poss.sort(cmp = myCmp)
print poss

for word in poss:
    print word, "\t...", word_score(word, letter_score_table)
