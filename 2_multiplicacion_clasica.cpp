    #include <iostream>
    #include <fstream>
    #include <chrono>
    #include <iomanip>
    #include <stdexcept>

    using namespace std;

    void inicializarMatrices(double **A, double **B, double **C, int n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                A[i][j] = i;
                B[i][j] = 1.0;
                C[i][j] = 0.0;
            }
        }
    }

    void multiplicarMatrices(double **A, double **B, double **C, int n) {
        for (int i = 0; i < n; i++) {
            for (int k = 0; k < n; k++) {
                double temp = A[i][k];
                for (int j = 0; j < n; j++) {
                    C[i][j] += temp * B[k][j];
                }
            }
        }
    }

    int main() {
        int tam[] = {16, 32, 64, 128, 256, 512, 1024, 2048};
        ofstream archivoCSV("resultados_multiplicacion_clasica.csv");

        if (!archivoCSV.is_open()) {
            cerr << "Error: no se pudo crear el archivo CSV." << endl;
            return 1;
        }

        archivoCSV << "Tamano,Tiempo_segundos\n";

        cout << fixed << setprecision(6);

        for (int i = 0; i < 8; i++) {
            int n = tam[i];

            double **A = nullptr;
            double **B = nullptr;
            double **C = nullptr;

            try {
                A = new double*[n];
                B = new double*[n];
                C = new double*[n];

                for (int j = 0; j < n; j++) {
                    A[j] = new double[n];
                    B[j] = new double[n];
                    C[j] = new double[n];
                }
            }
            catch (const bad_alloc&) {
                cerr << "Error: no hay suficiente memoria para " << n << " x " << n << "." << endl;
                delete[] A;
                delete[] B;
                delete[] C;
                archivoCSV.close();
                return 1;
            }

            inicializarMatrices(A, B, C, n);

            // Medir tiempo de multiplicación
            auto inicio = chrono::high_resolution_clock::now();
            multiplicarMatrices(A, B, C, n);
            auto fin = chrono::high_resolution_clock::now();

            double tiempo = chrono::duration<double>(fin - inicio).count();

            cout << "Tiempo de multiplicación para n = " << n << ": " << tiempo << " segundos" << endl;

            archivoCSV << n << "," << tiempo << "\n";

            // Liberar memoria
            for (int x = 0; x < n; x++) {
                delete[] A[x];
                delete[] B[x];
                delete[] C[x];
            }

            delete[] A;
            delete[] B;
            delete[] C;
        }

        archivoCSV.close();

        return 0;
    }
