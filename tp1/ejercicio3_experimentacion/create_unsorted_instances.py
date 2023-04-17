for power in range(16, 27):
    n = 2 ** power
    f = open("inputs/input_" + str(n), "w")
    input = range(0, n-1)
    f.write(str(n-1) + " ")
    for num in input:
        f.write(str(num) + " ")
    f.close()
