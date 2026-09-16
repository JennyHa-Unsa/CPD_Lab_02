
#include <iostream>
#include <chrono>
#include <fstream>
#include <vector>

using namespace std;

const vector<int> TAMAÑOS = {1000, 5000, 10000, 15000, 20000};

int main() {

    ofstream archivoCSV("1_bucles.csv");

    if (!archivoCSV.is_open()) {
        cerr << "Error al crear el archivo 1_bucles.csv" << endl;
        return 1;
    }

    archivoCSV << "MAX,Loop1_segundos,Loop2_segundos\n";

    for (int MAX : TAMAÑOS) {

        double duracionLoop1, duracionLoop2;

        double* A = new double[static_cast<size_t>(MAX) * MAX];
        double* x = new double[MAX];
        double* y = new double[MAX];

        /* Inicializar A y x, asignar y = 0 */
        for (int i = 0; i < MAX; i++) {
            x[i] = 2.0;
            y[i] = 0.0;
            for (int j = 0; j < MAX; j++) {
                A[static_cast<size_t>(i) * MAX + j] = i;
            }
        }

        /*** LOOP 01 ***/
        auto inicio = chrono::high_resolution_clock::now();
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                y[i] += A[static_cast<size_t>(i) * MAX + j] * x[j];
            }
        }
        auto fin = chrono::high_resolution_clock::now();
        duracionLoop1 = chrono::duration<double>(fin - inicio).count();

        /* Reiniciar y = 0 */
        for (int i = 0; i < MAX; i++) {
            y[i] = 0.0;
        }

        /*** LOOP 02 ***/
        inicio = chrono::high_resolution_clock::now();
        for (int j = 0; j < MAX; j++) {
            for (int i = 0; i < MAX; i++) {
                y[i] += A[static_cast<size_t>(i) * MAX + j] * x[j];
            }
        }
        fin = chrono::high_resolution_clock::now();
        duracionLoop2 = chrono::duration<double>(fin - inicio).count();

        /* Visualizar tiempos de ejecución */
        cout << "MAX = " << MAX << endl;
        cout << "Tiempo para el primer bucle: "<< duracionLoop1 << " segundos" << endl;
        cout << "Tiempo para el segundo bucle: "<< duracionLoop2 << " segundos" << endl;

        archivoCSV << MAX << "," << duracionLoop1 << ","<< duracionLoop2 << "\n";

        delete[] A;
        delete[] x;
        delete[] y;
    }

    archivoCSV.close();

    return 0;
}
