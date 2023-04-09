import numpy as np

def MC(i, j):

    posibles_cortes = 0

    min_ = np.inf
    for c in C:
        if i < c < j:
            min_ = min(min_, MC(i, c) + MC(c, j))
            posibles_cortes += 1
    
    if posibles_cortes == 0:
        return 0
    
    return (j-i) + min_

C = [2,4,7]
l = 10
dp = np.ones((l+1, l+1))

print(MC(0, l))