import subprocess
import sys

def leer_instancia(path_instancia):
    with open(path_instancia, "r") as f:
        return f.read()

def correr_instancia(archivo_instancia):
    # Leer archivo de la instancia.
    instancia = leer_instancia(archivo_instancia)
    
    # Crear proceso para ejecutar el codigo.
    process = subprocess.Popen(["./ejercicio_2"], stderr=subprocess.PIPE, stdout=subprocess.PIPE, stdin=subprocess.PIPE, universal_newlines = True)

    # Poner la instancia en la entrada estandar.
    process.stdin.write(instancia)
    process.stdin.flush()

    # Correr experimento.
    print(archivo_instancia)
    exit_code = process.wait()

    # Verificar que el proceso no fallo.
    if exit_code != 0: raise ValueError(F"Hubo un error en la experimentacion con la instancia {archivo_instancia}.")

    # Leer stderr
    time = process.stderr.read()

    # Leer la salida estandar
    resultado = process.stdout.read()
    print(resultado)
    print(round(float(time), 2))

    f = open("times.txt", "a")
    f.write(F"{round(float(time), 2)}\n")
    f.close()

    process.stdin.close()
    process.stdout.close()
    process.stderr.close()

file = open("times.txt", "a")
file.write(F"{sys.argv[1]}\n")
file.close()
correr_instancia(sys.argv[1])
