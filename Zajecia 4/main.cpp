//
// Created by Piotr Moszkowicz on 2019-03-21.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include "Matrix.h"
#include "Vector.h"

#include <gsl/gsl_eigen.h>

void saveToAll(std::string &fileName, double alfa, Vector *eval) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << alfa << "," << std::sqrt((*eval)[0]) << "," << std::sqrt((*eval)[1]) << "," << std::sqrt((*eval)[2]) << ","
         << std::sqrt((*eval)[3]) << "," << std::sqrt((*eval)[4]) << "," << std::sqrt((*eval)[5]) << std::endl;
    file.close();
}

void saveAllVectors(std::string &fileName, Vector *x, Matrix *evac, int n) {
    std::fstream file;
    file.open(fileName, std::ios::out);
    for (unsigned int i = 0; i < n; i++) {
        file << (*x)[i];
        for (unsigned int j = 0; j < n; j++) {
            file << "," << (*evac)(i, j);
        }
        file << std::endl;
    }

    file.close();
}

double getKroneckerDelta(int i, int j) {
    if (i == j) {
        return 1.0;
    }
    return 0.0;
}

double p(double x, double alfa) {
    return 1.0 + 4.0 * alfa * (x * x);
}

int main() {
    int L = 10;
    int n = 200;
    int N = 1;

    double deltaX = static_cast<double>(L) / (static_cast<double>(n) + 1.0);
    double deltaX2 = deltaX * deltaX;

    auto aMatrix = new Matrix(n, n);
    auto bMatrix = new Matrix(n, n);

    auto eval = new Vector(n);
    auto evac = new Matrix(n, n);

    auto xVector = new Vector(n);

    gsl_eigen_gensymmv_workspace *w = gsl_eigen_gensymmv_alloc(n);

    std::string fileNameAlfa0 = "alfa_0_data.csv";
    std::string fileNameAlfa100 = "alfa_100_data.csv";
    std::string fileNameAll = "data.csv";

    for (unsigned int alfa = 0; alfa <= 100; alfa += 2) {
        for (unsigned int i = 0; i < n; i++) {
            for (unsigned int j = 0; j < n; j++) {
                double x = (-static_cast<double>(L) / 2.0) + deltaX * (static_cast<double>(i) + 1.0);
                double aValue =
                        (-getKroneckerDelta(i, j + 1) + 2 * getKroneckerDelta(i, j) - getKroneckerDelta(i, j - 1)) /
                        deltaX2;
                double bValue = (p(x, alfa) / static_cast<double>(N)) * getKroneckerDelta(i, j);
                (*aMatrix)(i, j, aValue);
                (*bMatrix)(i, j, bValue);
                (*xVector)(i, x);
            }
        }
        gsl_eigen_gensymmv(aMatrix->getMatrixPtr(), bMatrix->getMatrixPtr(), eval->getVectorPtr(),
                           evac->getMatrixPtr(), w);
        gsl_eigen_gensymmv_sort(eval->getVectorPtr(), evac->getMatrixPtr(), GSL_EIGEN_SORT_ABS_ASC);
        saveToAll(fileNameAll, alfa, eval);
        if (alfa == 0) {
            saveAllVectors(fileNameAlfa0, xVector, evac, n);
        }
        if (alfa == 100) {
            saveAllVectors(fileNameAlfa100, xVector, evac, n);
        }
    }

    return 0;
}