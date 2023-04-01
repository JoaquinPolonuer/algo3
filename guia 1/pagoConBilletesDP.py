import numpy as np


def cc(B, i, j):

    # Me fijo si ya lo memorice
    if memo[i][j] != None:
        return memo[i][j]

    # Si no lo memorice, lo calculo
    if j <= 0:
        return (0, 0)

    if i == -1:
        return (np.inf, np.inf)

    bi = B[i]

    opcion1 = cc(B, i - 1, j - bi)
    opcion2 = cc(B, i - 1, j)

    # Memorizo y devuelvo
    memo[i][j] = min((bi + opcion1[0], 1 + opcion1[1]), opcion2)
    
    return memo[i][j]


# B = [6, 3, 3]
B = [2,3,5,10,20,20]

c = 14

memo = [[None for _ in range(c+1)] for _ in range(len(B))]

print(cc(B, len(B)-1, c))
