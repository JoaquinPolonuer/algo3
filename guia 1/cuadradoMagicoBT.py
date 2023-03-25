import numpy as np


def esCuadradoMagico(C):
    sumas_filas = np.sum(C, axis=0)
    sumas_columnas = np.sum(C, axis=1)

    suma_diagonal_1 = np.diag(C).sum()
    suma_diagonal_2 = np.diag(np.fliplr(C)).sum()

    return all(
        [
            suma_diagonal_2 == suma_diagonal_1,
            np.all(sumas_filas == suma_diagonal_1),
            np.all(sumas_columnas == suma_diagonal_1),
        ]
    )


def obtener_siguiente_posicion(i, j):
    if j + 1 < n:
        return (i, j + 1)
    else:
        return i + 1, 0


def cuantos_cuadrados_magicos(C, i, j, num_no_utilizados):
    global cuantos

    if i == n:
        if esCuadradoMagico(C):
            # print(C)
            cuantos += 1
    else:
        for num in num_no_utilizados:
            i_sig, j_sig = obtener_siguiente_posicion(i, j)

            nuevos_numeros_no_utilizados = list(num_no_utilizados)
            nuevos_numeros_no_utilizados.remove(num)

            C_modificada = C.copy()
            C_modificada[i, j] = num

            cuantos_cuadrados_magicos(C_modificada, i_sig, j_sig, nuevos_numeros_no_utilizados)

n = 3
C = np.zeros((n, n))
cuantos = 0

cuantos_cuadrados_magicos(C, 0, 0, range(1, n**2 + 1))
print(cuantos)
