//
// Created by Piotr Moszkowicz on 2019-03-28.
//

#include <iostream>
#include <array>
#include <cmath>
#include <fstream>
#include <iomanip>

void
saveNeededStuffToFile(std::string &fileName, int iterationNumber, double lambda) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << iterationNumber << " " << lambda << std::endl;
    file.close();
}

void saveMatrixToFile(std::string &fileName, std::array<std::array<double, 7>, 7> m) {
    std::fstream file;
    file.open(fileName, std::ios::out);
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            file << m[i][j];
            if (j != 6) {
                file << ", ";
            }
        }
        file << std::endl;
    }
    file.close();
}

double multiplyScalar(std::array<double, 7>& x, std::array<double, 7>& y) {
    double result = 0;
    for (int i = 0; i < 7; i++) {
        result += x[i] * y[i];
    }
    return result;
}



double norm(std::array<double, 7>& v) {
    return std::sqrt(multiplyScalar(v, v));
}

std::array<double, 7>& multiplyMatrixByVector(std::array<std::array<double, 7>, 7>& m, std::array<double, 7>& x, std::array<double, 7>& result) {
    for (int i = 0; i < 7; i++) {
        result[i] = 0;
        for (int j = 0; j < 7; j++) result[i] += m[i][j] * x[j];
    }
    return result;
}

void multiplyMatrixByMatrix(std::array<std::array<double, 7>, 7>& m1, std::array<std::array<double, 7>, 7>& m2, std::array<std::array<double, 7>, 7>& res) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            double resd = 0;
            for (int k = 0; k < 7; k++) {
                resd += m1[i][k] * m2[k][j];
            }
            res[i][j] = resd;
        }
    }
}

void transposeMatrix(std::array<std::array<double, 7>, 7>& m, std::array<std::array<double, 7>, 7>& res) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            res[j][i] = m[i][j];
        }
    }
}

void divideVectorByScalar(std::array<double, 7>& x, double div, std::array<double, 7>& res) {
    for (int i = 0; i < 7; i++) {
        res[i] = x[i] / div;
    }
}

void substractMatrixByScalar(std::array<std::array<double, 7>, 7>& A, double scalar, std::array<std::array<double, 7>, 7>& result) {
    for(int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            result[i][j] = A[i][j] - scalar;
        }
    }
}

void fillMatrixColumn(std::array<std::array<double, 7>, 7>& m, std::array<double, 7>& x, int k) {
    for (int i = 0; i < 7; i++) {
        m[i][k] = x[i];
    }
}

void refillWithTensorMultiply(std::array<std::array<double, 7>, 7>& bef, double lambda, std::array<double, 7>& x, std::array<std::array<double, 7>, 7>& res) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            res[i][j] = bef[i][j] - (lambda * x[i] * x[j]);
        }
    }
}

double countElementForFill(int i, int j) {
    return (1.0) / (std::sqrt(2.0 + std::abs(static_cast<double>(i) - static_cast<double>(j))));
}

void printVector(std::array<double, 7>& x) {
    for (int i = 0; i < 7; i++) {
        std::cout << std::setw(8) << "vector[" << i << "] = " << x[i] << std::endl;
    }
}

void printArray(std::array<std::array<double, 7>, 7>& x) {
    for (int i = 0; i < 7; i++) {
        for (int j = 0; j < 7; j++) {
            std::cout << "arr[" << i << "][" << j << "] = " << std::setw(12) << x[i][j] << "\t";
        }
        std::cout << std::endl;
    }
}

int main() {
    int n = 7;
    const int IT_MAX = 12;

    std::array<std::array<double, 7>, 7> A = {};

    for(int i = 0; i < 7; i++) {
        for(int j = 0; j < 7; j++) {
            A[i][j] = countElementForFill(i, j);
        }
    }

    std::array<std::array<double, 7>, 7> w = A;
    std::array<std::array<double, 7>, 7> wn = {};
    std::array<std::array<double, 7>, 7> X = {};
    std::array<std::array<double, 7>, 7> D = {};

    std::string fileNameLambdas = "data_lambdas.csv";

    std::ofstream ofs;
    ofs.open(fileNameLambdas, std::ofstream::out | std::ofstream::trunc);
    ofs.close();

    std::string fileNameMatrix = "data_matrix.csv";

    for(int k = 0; k < n; k++) {
        std::array<double, 7> xk0 = {};
        xk0.fill(1.0);
        double lambda = 0;

        for(int i = 0; i < IT_MAX; i++) {
            std::array<double, 7> xn = {};
            multiplyMatrixByVector(w, xk0, xn);
            lambda = multiplyScalar(xn, xk0) / multiplyScalar(xk0, xk0);
            std::cout << "Lambda[" << i << "] = " << lambda << std::endl;
            divideVectorByScalar(xn, norm(xn), xk0);
        }

        saveNeededStuffToFile(fileNameLambdas, k, lambda);
        refillWithTensorMultiply(w, lambda, xk0, wn);
        w = wn;
        fillMatrixColumn(X, xk0, k);
    }

    std::array<std::array<double, 7>, 7> AX = {};
    std::array<std::array<double, 7>, 7> XT = {};
    multiplyMatrixByMatrix(A, X, AX);
    transposeMatrix(X, XT);
    multiplyMatrixByMatrix(XT, AX, D);

    std::cout << std::endl << std::endl << "Macierz D:" << std::endl;
    printArray(D);

    saveMatrixToFile(fileNameMatrix, D);

    return 0;
}