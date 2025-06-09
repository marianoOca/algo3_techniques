#include <chrono>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

/* -- Definición de actividad -- */
struct actividad {
    int comienzo;
    int fin;
    int beneficio;
};

/* -- Definición de variables -- */
int n;                         // cantidad de actividades
vector<actividad> actividades; // vector de actividades

/* -- Función de ordenamiento según tiempo de fin -- */
void bucketSort() {
    vector<actividad> vacio;
    vector<vector<actividad>> buckets(2*n + 1, vacio);
    for (actividad act: actividades) buckets[act.fin].push_back(act);
    actividades.clear();
    for (vector<actividad> bucket: buckets) {
        for (actividad act: bucket) actividades.push_back(act);
    }
}

/* -- Función golosa -- */
vector<int> maxCardinal() {
    vector<int> solucion;
    int tiempoFinal = -1;
    for (int i = 0; i < n; i++) {
        if (tiempoFinal < actividades[i].comienzo) {
            solucion.push_back(i+1);
            tiempoFinal = actividades[i].fin;
        }
    }
    return solucion;
}

int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

/* -- Leemos de la entrada estandar -- */
    cin >> n;

/* -- Cargamos actividades -- */
    for (int i = 0; i < n; i++) {
        int com, fin, ben;
        cin >> com >> fin;
        actividad act = {com, fin, 1};
        actividades.push_back(act);
    }

/* -- Llamada a la funcion -- */
    auto start = chrono::steady_clock::now();

    bucketSort();

    vector<int> resultado = maxCardinal();

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double>(end - start).count();

/* -- Retornamos por stderr el tiempo de ejecucion -- */
    clog << total_time << endl;

/* -- Retornamos por la salida estandar el resultado -- */
    cout << resultado.size() << endl;
    for (int i = 0; i < resultado.size(); i++) cout << resultado[i] << " ";
    cout << endl;

    return 0;
}

/* -- couts para chequear que estamos leyendo bien -- */
    // for (actividad act: actividades) {
    //     cout << act.comienzo << " " << act.fin << " " << act.beneficio << endl;
    // }
