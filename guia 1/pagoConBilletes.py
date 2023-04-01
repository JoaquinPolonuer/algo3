import numpy as np


def cc(B, i, j):
    
    if j <= 0:
        return (0, 0)
    
    if i == -1:
        return (np.inf, np.inf)
    
    bi = B[i]

    opcion1 = cc(B, i - 1, j - bi)
    opcion2 = cc(B, i - 1, j)

    return min((bi + opcion1[0], 1 + opcion1[1]), opcion2)

B = [6,3,3]
c = 6

print(cc(B, len(B)-1, c))