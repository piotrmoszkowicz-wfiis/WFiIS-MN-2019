//
// Created by Piotr Moszkowicz on 2019-06-06.
//

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

double getStep(double a, double b, int n) {
    return (b - a) / std::pow(2, n);
}

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

template <int Len>
void printResults(std::array<std::array<double, Len>, Len>& tab) {
    for (int i = 0; i < Len; i++) {
        for (int j = 0; j < Len; j++) {
            if (j > i) {
                break;
            }
            std::cout << tab[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

template <int Len>
void romberMethod(std::array<std::array<double, Len>, Len>& tab, double (*func)(double), double a, double b) {
    tab[0][0] = (getStep(a, b, 0) / 2.0) * (func(a) + func(b));

    for (int i = 1; i < Len; i++) {
        double sum = 0;
        double step = getStep(a, b, i);

        for (int k = 1; k <= std::pow(2, i - 1); k++) {
            sum += func(a + (((2 * k) - 1) * step));
        }

        tab[i][0] = (tab[i - 1][0] / 2.0) + step * sum;
    }

    for (int j = 1; j < Len; j++) {
        for (int i = j; i < Len; i++) {
            double dk1 = tab[i][j - 1];
            double dk2 = tab[i - 1][j - 1];
            double pow = std::pow(4, j);

            tab[i][j] = ((pow * dk1) - dk2) / (pow - 1);
        }
    }
}

double ourFunction(double x) {
    if (x == 0) {
        x = x + 0.0000001;
    }
    return std::sin(x) / x;
}

double ourFunction2(double x) {
    if (x == 0) {
        x = x + 0.0000001;
    }
    return (std::cos(x) - std::exp(x)) / std::sin(x);
}

double ourFunction3(double x) {
    if (x == 0) {
        x = x + 0.0000001;
    }
    return (1.0 / ((1.0 / x) * std::exp(1 / x))) * (1.0 / (x * x));
}

template <int Len>
void saveResults(const std::string &fileName, std::array<std::array<double, Len>, Len>& tab) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    for (int i = 0; i < Len; i++) {
        for (int j = 0; j < Len; j++) {
            if (j > i) {
                break;
            }
            file << tab[i][j] << ",";
        }
        file << std::endl;
    }
    file.close();
}

int main() {
    // Polecenie 1
    const int n = 7;
    const std::string fileName1 = "data_zaj12_1.csv";

    std::array<std::array<double, n>, n> first{{0}};

    clearFile(fileName1);
    romberMethod<n>(first, ourFunction, 0.0, 1.0);
    printResults<n>(first);
    saveResults<n>(fileName1, first);

    std::cout << std::endl << std::endl;

    // Polecenie 2
    const int n2 = 15;
    const std::string fileName2 = "data_zaj12_2.csv";

    std::array<std::array<double, n2>, n2> second{{0}};

    clearFile(fileName2);
    romberMethod<n2>(second, ourFunction2, -1.0, 1.0);
    printResults<n2>(second);
    saveResults<n2>(fileName2, second);

    // Polecenie 3
    const int n3 = 7;
    const std::string fileName3 = "data_zaj12_3.csv";

    std::array<std::array<double, n3>, n3> third{{0}};

    clearFile(fileName3);
    romberMethod<n3>(third, ourFunction3, 0.0, 1.0);
    printResults<n3>(third);
    saveResults<n3>(fileName3, third);

    return 0;
}