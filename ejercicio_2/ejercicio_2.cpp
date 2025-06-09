#include <iostream>
#include <chrono>
#include <algorithm>
#include <vector>

using namespace std;

/* Declaración de variables -- */
vector<int> p;            // Influencia por actor
vector<vector<bool>> E;   // Matriz de amistades

int influenciaMaxima = 0; // Mayor influencia encontrada hasta el momento
vector<int> Qmax;         // Clique que proporciona influenciaMaxima

/* -- Declaracion de funciones -- */
void sacarNoAmigos(int ultimoActor, vector<int> &K, int &influenciaK);
bool sonTodosAmigos(vector<int> &K);
bool esNoAmigo(int actor, vector<int>& particion);
vector<vector<int>> independientes(vector<int> K);

/* -- Función de comparación según influencia -- */
struct {
    bool operator() (const int a, const int b) const {return p[a] > p[b];}
} cmp_mayor_menor;

/* -- Funcion de BT -- */
void calcularInfluenciaMaxima(vector<int> Q, vector<int> K, int influenciaQ, int influenciaK) {

    const auto particion = independientes(K);
    int influenciaParticion = 0;
    for(auto parte : particion) influenciaParticion += p[parte[0]];

    if (influenciaQ + influenciaParticion <= influenciaMaxima) return;
    if (influenciaK + influenciaQ < influenciaMaxima) return;
    if (sonTodosAmigos(K)) {
        for (int actor: K) {
            Q.push_back(actor + 1);
            influenciaQ += p[actor];
        }
        if (influenciaMaxima < influenciaQ) {
            Qmax = Q;
            influenciaMaxima = influenciaQ;
        }
        return;
    }

    // proximo actor a considerar
    auto it = K.begin();
    int actor = *it;
    // lo saco de K y resto su influencia de influenciaK
    K.erase(it);
    influenciaK -= p[actor];
    // guardamos K e influenciaK
    vector<int> K_sin = K;
    int influenciaK_sin = influenciaK;
    // llamada si agrego a actor
    Q.push_back(actor + 1);
    sacarNoAmigos(actor, K, influenciaK);
    calcularInfluenciaMaxima(Q, K, influenciaQ + p[actor], influenciaK);
    // llamada si no agrego a actor
    Q.pop_back();
    calcularInfluenciaMaxima(Q, K_sin, influenciaQ, influenciaK_sin);
}

/* -- Funciones auxiliares -- */
void sacarNoAmigos(int actor, vector<int> &K, int &influenciaK) {
    if (K.empty()) return;
    vector<int> nuevoK;
    for (int k : K) {
        if (!E[k][actor]) {
            influenciaK -= p[k];
        } else {
            nuevoK.push_back(k);
        }
    }
    K.assign(nuevoK.begin(), nuevoK.end());
}

bool sonTodosAmigos(vector<int> &K) {
    for (int actor: K) {
        for (int otroActor: K) {
            if (actor != otroActor && !E[actor][otroActor]) return false;
        }
    }
    return true;
}

bool esNoAmigo(int actor, vector<int>& particion) {
    for (int otro : particion) {
        if(E[actor][otro - 1]) return false;
    }
    return true;
}

vector<vector<int>> independientes(vector<int> K) {
    vector<vector<int>> res;
    vector<int> parte;

    while(!K.empty()) {
        vector<int> nuevoK;
        for (int k : K) {
            if (esNoAmigo(k, parte)) {
                parte.push_back(k + 1);
            } else {
                nuevoK.push_back(k);
            }
        }
        K.assign(nuevoK.begin(), nuevoK.end());
        res.push_back(parte);
        parte.clear();
    }
    return res;
}

/* -- main -- */
int main(int argc, char** argv) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    string trash; // para guardar las entradas que no nos interesan
    int n;        // cantidad de actores
    int m;        // cantidad de amistades

/* -- Leemos de la entrada estandar -- */
    cin >> trash >> trash >> n >> m;

    p.assign(n, 0);
    E.assign(n, vector<bool>(n, false));

/* -- Cargamos p -- */
    for (int i = 0; i < p.size(); i++) cin >> trash >> trash >> p[i];

/* -- Cargamos E -- */
    for (int i = 0; i < m; i++) {
        int amigo_1;
        int amigo_2;
        cin >> trash >> amigo_1 >> amigo_2;
        E[amigo_1-1][amigo_2-1] = true;
        E[amigo_2-1][amigo_1-1] = true;
    }

/* -- Parametros de la funcion -- */
    vector<int> Q;
    vector<int> K(n, 0);
    int influenciaQ = 0;
    int influenciaK = 0;

    // cargamos K
    for (int i = 0; i < K.size(); i++) K[i] = i;

    // ordenamos K de mayor a menor influencia
    stable_sort(K.begin(), K.end(), cmp_mayor_menor);

    // cargamos influenciaK
    for (int i = 0; i < K.size(); i++) influenciaK += p[K[i]];

/* -- Llamada a la funcion -- */
    auto start = chrono::steady_clock::now();

    calcularInfluenciaMaxima(Q, K, influenciaQ, influenciaK);

    auto end = chrono::steady_clock::now();
    double total_time = chrono::duration<double>(end - start).count();

/* -- Retornamos por stderr el tiempo de ejecucion -- */
    clog << total_time << endl;

/* -- Retornamos por la salida estandar el resultado -- */
    cout << influenciaMaxima << endl;
    for (int q: Qmax) cout << q << " ";
    cout << endl;

    return 0;
}

/* -- couts para chequear que estamos leyendo bien -- */
// cout << "n: " << n << endl;
// cout << "m: " << m << endl;
// cout << "p: ";
// for (int i = 0; i < p.size(); i++) {
//     cout << p[i] << " ";
// }
// cout << endl;
// cout << "E:" << endl;
// for (int i = 0; i < E.size(); i++) {
//     for (int j = 0; j < E[0].size(); j++) {
//         cout << E[i][j] << " ";
//     }
//     cout << endl;
// }
