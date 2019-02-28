#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <iostream>
#include <iomanip>
#include <fstream>

gsl_matrix* fillMatrix(unsigned int size) {
    const double x = 3.0;
    gsl_matrix *A = gsl_matrix_calloc(size, size);
    for(unsigned int i=0; i < size; i++) {
        for(unsigned int j=0; j < size; j++) {
            double value = 1.0 / (i + j + x);
            gsl_matrix_set(A, i, j, value);
        }
    }
    return A;
}

void printMatrix(gsl_matrix *A, unsigned int size) {
    std::cout << "Macierz: " << std::endl;
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j< size; j++) {
            double v = gsl_matrix_get(A, i, j);
            std::cout << std::setw(15) << v << " ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl;
}

gsl_permutation* generatePermutationVector(unsigned int size) {
    return gsl_permutation_calloc(size);
}

double countWyznacznikFromDiagonal(gsl_matrix *A, unsigned int size) {
    double result = 1.0;
    for(unsigned int i = 0; i < size; i++) {
        result *= gsl_matrix_get(A, i, i);
    }
    return result;
}

double* findDiagonalItems(gsl_matrix *A, unsigned int size) {
    double *diagonal = new double[size];
    for(unsigned int i = 0; i < size; i++) {
        diagonal[i] = gsl_matrix_get(A, i, i);
    }
    return diagonal;
}

void saveNeededStuffToFile(gsl_matrix *A, unsigned int size, std::string filename, double* diagonal, gsl_matrix *B, double norm) {
    std::fstream file;
    double wyznacznik = countWyznacznikFromDiagonal(A, 4);
    file.open(filename, std::ios::out);
    file << "Wyznacznik: " << wyznacznik << std::endl;
    file << "Elementy na diagonali: " << std::endl;
    for(unsigned int i = 0; i < size; i++) {
        file << diagonal[i] << std::endl;
    }
    file << "Macierz odwrotna: " << std::endl;
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; i < size; i++) {
            file << gsl_matrix_get(B, i, j) << " ";
        }
        file << std::endl;
    }
    file << "Wskaznik uwarunkowania: " << norm << std::endl;
    file.close();
}

gsl_matrix* findOdwrotnaMatrix(gsl_matrix *A, unsigned int size, gsl_permutation *p) {
    gsl_vector *w = gsl_vector_calloc(size);
    gsl_vector *r = gsl_vector_calloc(size);
    gsl_matrix *B = gsl_matrix_calloc(size, size);

    for(unsigned int i = 0;i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
            double toSet = 0.0;
            if (i == j) {
                toSet = 1.0;
            }
            gsl_vector_set(w, j, toSet);
        }

        gsl_linalg_LU_solve(A, p, w, r);

        for(unsigned int j = 0; j < size; j++) {
            gsl_matrix_set(B, j, i, gsl_vector_get(r, j));
        }
    }
    return B;
}

gsl_matrix* mnozMacierz(gsl_matrix *A, gsl_matrix *B, unsigned int size) {
    gsl_matrix *C = gsl_matrix_calloc(size, size);

    for(int i=0; i < size; i++) {
        for(int j=0; j < size; j++) {
            double sum = 0.0;
            for(int k=0; k < size; k++) {
                sum += (gsl_matrix_get(A, i, k) * gsl_matrix_get(B, k, j));
            }
            gsl_matrix_set(C, i, j, sum);
        }
    }

    return C;
}

double findMaxModule(gsl_matrix *A, unsigned int size) {
    double max = abs(gsl_matrix_get(A, 0, 0));
    for(unsigned int i = 0;i < size; i++) {
        for(unsigned int j=0; j < size; j++) {
            double m = abs(gsl_matrix_get(A, i, j));
            if (m > max) {
                max = m;
            }
        }
    }
    return max;
}

gsl_matrix* copyMatrix(gsl_matrix *A, unsigned int size) {
    gsl_matrix *COPY = gsl_matrix_calloc(size, size);
    for(unsigned int i = 0; i < size; i++) {
        for(unsigned int j = 0; j < size; j++) {
            gsl_matrix_set(COPY, i, j, gsl_matrix_get(A, i, j));
        }
    }
    return COPY;
}

int main() {
    gsl_matrix *A = fillMatrix(4);
    gsl_permutation *p = generatePermutationVector(4);
    int* signum = new int;

    printMatrix(A, 4);

    gsl_matrix *A_cp = copyMatrix(A, 4);

    gsl_linalg_LU_decomp(A, p, signum);

    printMatrix(A, 4);
    double* diagonal = findDiagonalItems(A, 4);

    gsl_matrix *B = findOdwrotnaMatrix(A, 4, p);

    printMatrix(B, 4);

    gsl_matrix *C = mnozMacierz(A, B, 4);

    printMatrix(C, 4);

    double wsk = findMaxModule(A_cp, 4) * findMaxModule(B, 4);

    saveNeededStuffToFile(A, 4, "results.txt", diagonal, B, wsk);

    delete signum;
    delete [] diagonal;

    return 0;
}