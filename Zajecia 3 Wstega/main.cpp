//
// Created by Piotr Moszkowicz on 2019-03-06.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <array>

void
saveNeededStuffToFile(std::string &fileName, unsigned int iterationNumber, double alfaK, double normRest,
                      double normSolv) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << iterationNumber << " " << normRest << " " << alfaK << " " << normSolv << std::endl;
    file.close();
}

void saveNormStuffToFile(std::string& fileName, unsigned int iterationNumber, double norm) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << iterationNumber << "," << norm << std::endl;
    file.close();
}

double countNorm(double rkt, double rk) {
    return sqrt(rkt * rk);
}

double multiplyScalar(std::array<double, 1000>& x, std::array<double, 1000>& y) {
    double result = 0;
    for (int i = 0; i < 1000; i++) {
        result += x[i] * y[i];
    }
    return result;
}

double norm(std::array<double, 1000>& v) {
    return multiplyScalar(v, v);
    // return std::sqrt(multiplyScalar(v, v));
}

std::array<double, 1000> multiplyByScalar(std::array<double, 1000>& x, double scalar) {
    std::array<double, 1000> result = std::array<double, 1000>();
    for (int i = 0; i < 1000; i++) {
        result[i] = x[i] * scalar;
    }
    return result;
}

std::array<double, 1000> minusVectors(std::array<double, 1000>& x, std::array<double, 1000>& y) {
    std::array<double, 1000> result = std::array<double, 1000>();
    for (int i = 0; i < 1000; i++) {
        // std::cout << x[i] << "-" << y[i] << std::endl;
        result[i] = x[i] - y[i];
    }
    return result;
}

std::array<double, 1000> plusVectors(std::array<double, 1000>& x, std::array<double, 1000>& y) {
    std::array<double, 1000> result = std::array<double, 1000>();
    for (int i = 0; i < 1000; i++) {
        result[i] = x[i] + y[i];
    }
    return result;
}

void printVector(std::array<double, 1000>& x) {
    for (int i = 0; i < 1000; i++) {
        std::cout << "vector[" << i << "] = " << x[i] << std::endl;
    }
}

std::array<double, 1000>& multiplyMatrixByVector(std::array<std::array<double, 1000>, 1000>& m, std::array<double, 1000>& x, std::array<double, 1000>& result) {
    for (int i = 0; i < 1000; i++) {
        int jmin = std::max(0, i - 5);
        int jmax = std::min(i + 5, 1000 - 1);
        result[i] = 0;
        for (int j = jmin; j <= jmax; j++) result[i] += m[i][j] * x[j];
    }
    return result;
}

int main() {
    const unsigned int n = 1000;

    std::array<std::array<double, n>, n> arr{};

    std::array<double, n> b{};
    std::array<double, n> x{};
    std::array<double, n> rk{};
    std::array<double, n> rk1{};
    std::array<double, n> v{};

    const double s = std::pow(10, -6);

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            auto val = std::abs(static_cast<double>(i) - static_cast<double>(j));

            if (val <= 5) {
                arr[i][j] = 1.0 / (1.0 + val);
            } else {
                arr[i][j] = 0.0;
            }
        }
    }

    std::cout << "after first for" << std::endl;

    for (unsigned int i = 0; i < n; i++) {
        b[i] = (static_cast<double>(i) + 1);
    }

    x.fill(0);

    unsigned int numOfIter = 1;
    std::string fileName = "data.csv";
    std::string fileNameNormX = "data_x.csv";
    std::string fileNameNormR = "data_r.csv";

    std::array<double, 1000> mult{};
    multiplyMatrixByVector(arr, x, mult);
    rk = minusVectors(b, mult);
    v = minusVectors(b, mult);

    while (multiplyScalar(rk, rk) > s) {
        std::array<double, 1000> mult2{};
        multiplyMatrixByVector(arr, v, mult2);

        double ak = multiplyScalar(rk, rk) / multiplyScalar(mult2, v);

        std::array<double, 1000> mult3 = multiplyByScalar(v, ak);
        std::array<double, 1000> mult4 = multiplyByScalar(mult2, ak);
        x = plusVectors(x, mult3);
        rk1 = minusVectors(rk, mult4);

        double bk = multiplyScalar(rk1, rk1) / multiplyScalar(rk, rk);
        std::array<double, 1000> mult5 = multiplyByScalar(v, bk);
        v = plusVectors(rk1, mult5);

        numOfIter++;
        /* saveNeededStuffToFile(fileName, numOfIter, ak, norm(rk), norm(x));
        saveNormStuffToFile(fileNameNormX, numOfIter, norm(x));
        saveNormStuffToFile(fileNameNormR, numOfIter, norm(rk)); */
        std::cout << "NumOfIter: " << numOfIter << multiplyScalar(rk, rk) << std::endl;
a
        rk = rk1;
    }

    printVector(x);
    std::cout << "Ilosc iteracji: " << numOfIter << std::endl;
    std::cout << "Norm: " << norm(rk) << std::endl;

    return 0;
}