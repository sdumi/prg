################################################## SUDOKU tester
# Purpose: test if a sudoku configuration is valid or not.
# Input: "sudoku.txt": file containing the sudoku configuration (numbers in a 9x9 matrix)
# Output: OK, NOK.


def zeros(*shape):
    """
    returns a matrix filled with 0s. structure of matrix is defined by 
    *shape.
    Ex: zeros(3, 4)
    """
    if len(shape) == 0:
        return 0
    car = shape[0]
    cdr = shape[1:]
    return [zeros(*cdr) for i in range(car)]

def get_sudoku(fname = "sudoku.txt"):
    "read a text file containing the sudoku"
    fileContent = file(fname).readlines()
    mx = zeros(9,9)
    #try to assign fileContent to mx
    #LATER: create mx in a more flexible way
    i = 0
    j = 0
    for line in fileContent:
        j = 0
        for number  in line:
            if (j % 2 == 0):
                mx[i][j/2] = number
            j = j + 1
        i = i + 1
    return mx

def print_sudoku(mx):
    for i in range(0,9):
        str = ""
        for j in range(0,9):
            str += mx[i][j]
            str += " "
            if (((j+1) % 3) == 0):
                str += "  "
        if i % 3 == 0:
            print ""
        print str
    print ""
            
def validate_line(line):
    [d.setdefault(x,x) for d in [{}] for x in line if x not in d]
    return (len(d) == len(line))

def validate_column(col):
    return validate_line(col)

def validate_square(sq):
    return validate_line(sq)

def validate_sudoku(mx):
    """
    will validate a sudoku matrix:
    - no duplicate numbers on line
    - no duplicate numbers on column
    - no duplicate numbers inside a 3x3 matrix
    """
    for line in range(0,9):
        if not validate_line(mx[line]):
            print "Error on line:"
#            print line
            return 1==0
    # read a column and validate it:
    for i in range(0,9):
        col = []
        for j in range(0,9):
            col.append(mx[j][i])
        if not validate_column(col):
            print "Error on column: ", i
#            print col
            return 1==0
    # read each 3x3 square and validate it
    # we read the square in a list and we validate it just like a line
    # we have 9 squares:
    for sq_i in range(0,3):
        for sq_j in range(0,3):
            sq = []
            for i in range(0,3):
                for j in range(0,3):
                    sq.append(mx[i + sq_i*3][j + sq_j*3])
            if not validate_square(sq):
                print "Error on square: (", sq_i+1, ", ", sq_j+1, ")"
#                print sq
                return 1==0

################################################## Main body
mx = get_sudoku()
print_sudoku(mx)
validate_sudoku(mx)
