import numpy as np

# No se como hacer para que esta solucion no sea O(n)
def es_cuadrado_magico(): 
    return all(
        [
            suma_diagonales[0] == suma_diagonales[1],
            np.all(suma_filas == suma_diagonales[0]),
            np.all(suma_columnas == suma_diagonales[0]),
        ]
    )

def obtener_siguiente_posicion(i, j):
    if j + 1 < n:
        return (i, j + 1)
    else:
        return i + 1, 0

def cuantos_cuadrados_magicos(i, j):
    global cuantos
    if i == n:
        if es_cuadrado_magico():
            cuantos += 1
    else:
        for num in range(1, n**2 + 1):
            if usados[num - 1]:
                continue

            i_sig, j_sig = obtener_siguiente_posicion(i, j)

            C[i][j] = num
            usados[num - 1] = 1

            suma_filas[i] += num
            suma_columnas[j] += num
            if i == j:
                suma_diagonales[0] += num
            if i == n - j - 1: 
                suma_diagonales[1] += num           
            
            if suma_filas[i] <= (n**3 + n) / 2 \
                and suma_columnas[j] <= (n**3 + n) / 2 :
                cuantos_cuadrados_magicos(i_sig, j_sig)

            usados[num-1] = 0 
            suma_filas[i] -= num
            suma_columnas[j] -= num

            if i == j:
                suma_diagonales[0] -= num
            if i == n - j - 1: 
                suma_diagonales[1] -= num    


n = 3
C = np.zeros((n, n))

suma_filas = np.zeros(n)
suma_columnas = np.zeros(n)
suma_diagonales = np.zeros(2)
usados = np.zeros(n**2)

cuantos = 0
cuantos_cuadrados_magicos(0,0)
print(cuantos)