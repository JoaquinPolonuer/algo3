import numpy as np

np.random.seed(1337)

for power in range(16, 27):
    n = 2 ** power
    f = open("inputs/input_" + str(n), "w")
    input = np.random.randint(0,2*n,n)
    for num in input:
        f.write(str(num) + " ")
    f.close()
