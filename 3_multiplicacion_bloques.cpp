#include <iostream>
#include <chrono>
#include <cmath>
#include <fstream>

using namespace std;

void  inicializarMatrices(double **A, double **B, double **C, int n) {
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

void multiplicarMatricesBloques(double **A, double **B, double **C, int n, int blockSize) {
    for (int i0 = 0; i0 < n; i0 += blockSize) {
        for (int j0 = 0; j0 < n; j0 += blockSize) {
            for (int k0 = 0; k0 < n; k0 += blockSize) {
                // Bloques: i0, j0, k0
                int i_end = (i0 + blockSize) < n ? (i0 + blockSize) : n;
                int j_end = (j0 + blockSize) < n ? (j0 + blockSize) : n;
                int k_end = (k0 + blockSize) < n ? (k0 + blockSize) : n;
                
                for (int i = i0; i < i_end; i++) {
                    for (int k = k0; k < k_end; k++) {
                        double temp = A[i][k];
                        for (int j = j0; j < j_end; j++) {
                            C[i][j] += temp * B[k][j];
                        }
                    }
                }
            }
        }
    }
}

int main() {
    ofstream csvFile("resultados_bloques.csv");
    csvFile << "Tamaño,BlockSize,TiempoSegundos" << endl;

    int tam[] = {16, 32, 64, 128, 256, 512, 1024, 2048};
    int blocks[] = {2, 4, 8, 16, 32, 64, 128, 256};
    
    for (int i = 0; i < 8; i++) {
        int n = tam[i];
        double **A = new double*[n];
        double **B = new double*[n];
        double **C = new double*[n];

        for (int j = 0; j < n; j++) {
            A[j] = new double[n];
            B[j] = new double[n];
            C[j] = new double[n];
        }

        inicializarMatrices(A, B, C, n);

        for(int b = 0; b < 8; b++) {
            int blockSize = blocks[b];
            if (blockSize > n) continue; // Skip si el blockSize es mayor que n

            // Resetear matrix C a cero antes de cada multiplicación
            for (int x = 0; x < n; x++)
                for (int y = 0; y < n; y++)
                    C[x][y] = 0.0;

            // Medir tiempo de multiplicación por bloques
            auto inicio = chrono::high_resolution_clock::now();
            multiplicarMatricesBloques(A, B, C, n, blockSize);
            auto fin = chrono::high_resolution_clock::now();

            double tiempo = chrono::duration<double>(fin - inicio).count();
            cout << "Tiempo de multiplicación por bloques para n = " << n 
                 << " y blockSize = " << blockSize << ": " << tiempo << " segundos" << endl;
            
            csvFile << n << "," << blockSize << "," << tiempo << endl;
        }
        cout << "----------------------------------------" << endl;

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
    
    csvFile.close();
    return 0;
}