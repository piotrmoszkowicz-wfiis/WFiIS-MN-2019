//
// Created by Piotr Moszkowicz on 2019-04-25.
//

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>

#include "Matrix.h"
#include "Vector.h"

double func1(double x) {
    return 1.0 / (1.0 + (x * x));
}

double func2(double x) {
    return std::cos(2 * x);
}

double delta(double xmin, double xmax, int n) {
    return (xmax - xmin) / static_cast<double>(n - 1);
}

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveToFile(const std::string &fileName, double x, double y, double yFunc) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << "," << y << "," << yFunc << "\n";
    file.close();
}

double h(double x, double x1) {
    return x - x1;
}

double lambda(double h, double h1) {
    return h1 / (h + h1);
}

double mi(double lambda) {
    return 1.0 - lambda;
}

double d(double h, double h1, double y, double y1, double y2) {
    return (6.0 / (h + h1)) * ((y1 - y) / h1 - (y - y2) / h);
    // return (6.0 / (h + h1)) * (((y1 - y) / h1) - ((y - y2) / h));
}

gsl_permutation *generatePermutationVector(unsigned int size) {
    return gsl_permutation_calloc(size);
}

template<int Len>
void getM(std::array<double, Len> &x, std::array<double, Len> &y, std::array<double, Len> &m, int n, double &alfa,
          double &beta) {
    auto A = new Matrix(n, n);
    auto vec = new Vector(n);
    auto solveVector = new Vector(n);
    gsl_permutation *p = generatePermutationVector(n);
    std::array<double, Len - 2> lambdas{};
    auto signum = new int;

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            (*A)(i, j, 0.0);
        }
        (*vec)(i, 0.0);
    }


    // Diagonala
    (*A)(0, 0, 1.0);
    (*A)(n - 1, n - 1, 1.0);
    for (unsigned int i = 1; i < n - 1; i++) {
        (*A)(i, i, 2.0);
    }

    // Nad diagonala
    for (unsigned int i = 2; i < n; i++) {
        const double hValueCur = h(x[i - 1], x[i - 2]);
        const double hValueNext = h(x[i - 1], x[i - 2]);
        lambdas[i - 2] = lambda(hValueCur, hValueNext);
        (*A)(i - 1, i, lambdas[i - 2]);
    }

    // Pod diagonala
    for (unsigned int i = 0; i < n - 2; i++) {
        (*A)(i + 1, i, mi(lambdas[i]));
    }

    std::cout << *A << std::endl;

    // Wektor wyrazów wolnych
    (*vec)(0, alfa);
    (*vec)(n - 1, beta);

    for (unsigned int i = 1; i < n - 1; i++) {
        const double hValueCur = h(x[i], x[i - 1]);
        const double hValueNext = h(x[i + 1], x[i]);
        (*vec)(i, d(hValueCur, hValueNext, y[i], y[i + 1], y[i - 1]));
    }

    std::cout << *vec << std::endl;

    // Rozwiązanie równania i zapisanie wyników do m
    gsl_linalg_LU_decomp(A->getMatrixPtr(), p, signum);
    gsl_linalg_LU_solve(A->getMatrixPtr(), p, vec->getVectorPtr(), solveVector->getVectorPtr());

    std::cout << *solveVector << std::endl;

    for (unsigned int i = 0; i < n - 1; i++) {
        m[i] = (*solveVector)[i];
    }
}

double aConst(double y, double y1, double h, double m, double m1) {
    return ((y - y1) / h) - ((h / 6.0) * (m - m1));
}

double bConst(double y, double m, double h) {
    return y - (m * ((h * h) / 6));
}

template<int Len>
double
getSx(std::array<double, Len> &x, std::array<double, Len> &y, std::array<double, Len> &m, int n, double xValue) {
    int i = 0;

    for (unsigned int j = 1; j < n; j++) {
        if (xValue >= x[j - 1] && xValue <= x[j]) {
            i = j;
            break;
        }
    }

    const double hValueCur = h(x[i], x[i - 1]);
    return m[i - 1] * (std::pow(x[i] - xValue, 3) / (6.0 * hValueCur)) +
           m[i] * (std::pow(xValue - x[i - 1], 3) / (6.0 * hValueCur)) +
           aConst(y[i], y[i - 1], hValueCur, m[i], m[i - 1]) * (xValue - x[i - 1]) +
           bConst(y[i - 1], m[i - 1], hValueCur);
}

int main() {
    double alfa = 0, beta = 0;
    double alfaCos = 0, betaCos = 0;
    const double xmin = -5;
    const double xmax = 5;

    const double deltaX = 1.0 / 100.0;

    const int n1 = 21;

    const std::string fileNamen1 = "data_sklej_n1.csv";
    const std::string fileNamen1Cos = "data_sklej_cos_n1.csv";

    clearFile(fileNamen1);
    clearFile(fileNamen1Cos);

    std::array<double, n1> xn1{};
    std::array<double, n1> yn1{};
    std::array<double, n1> mn1{};

    std::array<double, n1> xn1cos{};
    std::array<double, n1> yn1cos{};
    std::array<double, n1> mn1cos{};

    for (int i = 0; i < n1; i++) {
        xn1[i] = xmin + (delta(xmin, xmax, n1) * i);
        yn1[i] = func1(xn1[i]);

        xn1cos[i] = xmin + (delta(xmin, xmax, n1) * i);
        yn1cos[i] = func2(xn1[i]);
    }

    getM<n1>(xn1, yn1, mn1, n1, alfa, beta);
    getM<n1>(xn1cos, yn1cos, mn1cos, n1, alfaCos, betaCos);

    for (unsigned int i = 0; i <= 100; i++) {
        const double curX = xmin + (i * 0.1);

        double valueXn1 = getSx<n1>(xn1, yn1, mn1, n1, curX);
        double valueXn1cos = getSx<n1>(xn1cos, yn1cos, mn1cos, n1, curX);

        saveToFile(fileNamen1, curX, valueXn1, func1(curX));
        saveToFile(fileNamen1Cos, curX, valueXn1cos, func2(curX));
    }

    return 0;
}
