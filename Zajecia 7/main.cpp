//
// Created by Piotr Moszkowicz on 2019-04-11.
//

#include <array>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

double func(double x) {
    return std::exp(-(x * x));
}

double delta(double xmin, double xmax, int n) {
    return (xmax - xmin) / static_cast<double>(n);
}

double chebyshev(double xmin, double xmax, int n, int m) {
    return 0.5 * ((xmax - xmin) *
                  std::cos(M_PI * ((2.0 * static_cast<double>(m) + 1.0) / (2.0 * static_cast<double>(n) + 2.0))) +
                  (xmin + xmax));
}

template<int Len>
double lagrange(std::array<double, Len + 1>& x, std::array<double, Len + 1>& y, double xVal) {
    double w = 0;
    for (int j = 0; j <= Len; j++) {
        double u = 1.0;
        for (int i = 0; i <= Len; i++) {
            if (i != j) {
                u *= (xVal - x[i]) / (x[j] - x[i]);
            }
        }
        w += y[j] * u;
    }
    return w;
}

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveToFile(const std::string &fileName, double x, double y) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << "," << y << "\n";
    file.close();
}

int main() {
    double xmin = -5;
    double xmax = 5;

    const int n1 = 5;
    const int n2 = 10;
    const int n3 = 15;
    const int n4 = 20;

    const std::string fileNamen1 = "data_lagrange_n1.csv";
    const std::string fileNamen2 = "data_lagrange_n2.csv";
    const std::string fileNamen3 = "data_lagrange_n3.csv";
    const std::string fileNamen4 = "data_lagrange_n4.csv";

    const std::string fileNamen1c = "data_lagrange_n1_chebyshev.csv";
    const std::string fileNamen2c = "data_lagrange_n2_chebyshev.csv";
    const std::string fileNamen3c = "data_lagrange_n3_chebyshev.csv";
    const std::string fileNamen4c = "data_lagrange_n4_chebyshev.csv";

    clearFile(fileNamen1);
    clearFile(fileNamen2);
    clearFile(fileNamen3);
    clearFile(fileNamen4);

    clearFile(fileNamen1c);
    clearFile(fileNamen2c);
    clearFile(fileNamen3c);
    clearFile(fileNamen4c);

    std::array<double, n1 + 1> xn1{};
    std::array<double, n1 + 1> yn1{};

    std::array<double, n2 + 1> xn2{};
    std::array<double, n2 + 1> yn2{};

    std::array<double, n3 + 1> xn3{};
    std::array<double, n3 + 1> yn3{};

    std::array<double, n4 + 1> xn4{};
    std::array<double, n4 + 1> yn4{};

    std::array<double, n1 + 1> cxn1{};
    std::array<double, n1 + 1> cyn1{};

    std::array<double, n2 + 1> cxn2{};
    std::array<double, n2 + 1> cyn2{};

    std::array<double, n3 + 1> cxn3{};
    std::array<double, n3 + 1> cyn3{};

    std::array<double, n4 + 1> cxn4{};
    std::array<double, n4 + 1> cyn4{};

    for (int i = 0; i <= n1; i++) {
        xn1[i] = xmin + (delta(xmin, xmax, n1) * i);
        yn1[i] = func(xn1[i]);

        cxn1[i] = chebyshev(xmin, xmax, n1, i);
        cyn1[i] = func(cxn1[i]);
    }

    for (int i = 0; i <= n2; i++) {
        xn2[i] = xmin + (delta(xmin, xmax, n2) * i);
        yn2[i] = func(xn2[i]);

        cxn2[i] = chebyshev(xmin, xmax, n2, i);
        cyn2[i] = func(cxn2[i]);
    }

    for (int i = 0; i <= n3; i++) {
        xn3[i] = xmin + (delta(xmin, xmax, n3) * i);
        yn3[i] = func(xn3[i]);

        cxn3[i] = chebyshev(xmin, xmax, n3, i);
        cyn3[i] = func(cxn3[i]);
    }

    for (int i = 0; i <= n4; i++) {
        xn4[i] = xmin + (delta(xmin, xmax, n4) * i);
        yn4[i] = func(xn4[i]);

        cxn4[i] = chebyshev(xmin, xmax, n4, i);
        cyn4[i] = func(cxn4[i]);
    }

    for (int i = 0; i <= 100; i++) {
        const double curX = xmin + (i * 0.1);

        double wn1 = lagrange<n1>(xn1, yn1, curX);
        double wn2 = lagrange<n2>(xn2, yn2, curX);
        double wn3 = lagrange<n3>(xn3, yn3, curX);
        double wn4 = lagrange<n4>(xn4, yn4, curX);

        double cwn1 = lagrange<n1>(cxn1, cyn1, curX);
        double cwn2 = lagrange<n2>(cxn2, cyn2, curX);
        double cwn3 = lagrange<n3>(cxn3, cyn3, curX);
        double cwn4 = lagrange<n4>(cxn4, cyn4, curX);

        saveToFile(fileNamen1, curX, wn1);
        saveToFile(fileNamen2, curX, wn2);
        saveToFile(fileNamen3, curX, wn3);
        saveToFile(fileNamen4, curX, wn4);

        saveToFile(fileNamen1c, curX, cwn1);
        saveToFile(fileNamen2c, curX, cwn2);
        saveToFile(fileNamen3c, curX, cwn3);
        saveToFile(fileNamen4c, curX, cwn4);
    }
    return 0;
}