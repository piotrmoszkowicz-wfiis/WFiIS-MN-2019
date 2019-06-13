//
// Created by Piotr Moszkowicz on 2019-06-13.
//

#include <array>
#include <cmath>
#include <iostream>
#include <fstream>

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveResults(const std::string &fileName, std::array<double, 2000>& tab) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    for (int i = 0; i < 2000 - 3; i++) {
        file << tab[i] << "," << tab[i + 1] << "," << tab[i + 2] << "," << tab[i + 3] << std::endl;
    }
    file.close();
}

void saveResults(const std::string &fileName, double x, double y, double z) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << "," << y << "," << z << std::endl;
    file.close();
}

void saveResults(const std::string &fileName, double x) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << std::endl;
    file.close();
}

double gen1() {
    static long int x = 10;
    int a = 17;
    int c = 0;
    long int m = static_cast<long>(std::pow(2, 13)) - 1;

    x = ((a * x) + c) % m;
    return x / (m + 1.0);
}

double gen2() {
    static long int x = 10;
    int a = 85;
    int c = 0;
    long int m = static_cast<long>(std::pow(2, 13)) - 1;

    x = ((a * x) + c) % m;
    return x / (m + 1.0);
}

double gen3() {
    static long int x2 = 10;
    static long int x1 = 10;
    static long int x0 = 10;

    auto m = static_cast<long int>((std::pow(2, 32) - 5));

    long int x = (1176 * x0 + 1476 * x1 + 1776 * x2) % m;

    x2 = x1;
    x1 = x0;
    x0 = x;

    return x / (m + 1.0);
}

double vectorLength(double x, double y, double z) {
    return std::sqrt(x * x + y * y + z * z);
}

double countR(double delta, double j ) {
    return delta * j;
}

double countSphere(double r) {
    return (4.0 / 3.0) * M_PI * (r * r * r);
}

int main() {
    // Punkt 1.1.1
    const int n = 2000;
    std::array<double, n> first{};
    first.fill(0);
    std::string fileName1 = "data_13_1.csv";

    std::array<double, n> second{};
    second.fill(0);
    std::string fileName2 = "data_13_2.csv";

    clearFile(fileName1);
    clearFile(fileName2);

    for (int i = 0; i < n; i++) {
        first[i] = gen1();
        second[i] = gen2();
    }

    saveResults(fileName1, first);
    saveResults(fileName2, second);

    // Punkt 1.1.2
    std::array<double, n> third{};
    first.fill(0);
    std::string fileName3 = "data_13_3.csv";

    clearFile(fileName3);

    for (int i = 0; i < n; i++) {
        third[i] = gen3();
    }

    saveResults(fileName3, third);

    // Punkt 1.2
    const int n1 = static_cast<int>(std::pow(10, 7));
    std::string fileName4 = "data_13_4.csv";
    std::string fileName5 = "data_13_5.csv";
    std::string fileName6 = "data_13_6.csv";
    std::string fileName7 = "data_13_7.csv";

    clearFile(fileName4);
    clearFile(fileName5);
    clearFile(fileName6);
    clearFile(fileName7);

    const int k = 10;
    const double delta = 1.0 / k;
    std::array<int, k + 1> p{0};

    for (int i = 0; i < n1; i++) {
        double u1 = gen3();
        double u2 = gen3();
        double u3 = gen3();
        double u4 = gen3();

        double x = std::sqrt(-2 * std::log(1 - u1)) * std::cos(2 * M_PI * u2);
        double y = std::sqrt(-2 * std::log(1 - u1)) * std::sin(2 * M_PI * u2);
        double z = std::sqrt(-2 * std::log(1 - u3)) * std::cos(2 * M_PI * u4);

        double r = vectorLength(x, y, z);

        x /= r;
        y /= r;
        z /= r;

        if (n1 < 2000) {
            saveResults(fileName4, x, y, z);
        }

        double u5 = gen3();
        double si = std::pow(u5, 1.0 / 3.0);

        x *= si;
        y *= si;
        z *= si;

        if (n1 < 2000) {
            saveResults(fileName5, x, y, z);
        }

        double ri = vectorLength(x, y, z);
        int index = static_cast<int>(ri / delta) + 1;
        p[index]++;
    }

    for (int i = 1; i <= k; i++) {
        if (n1 < 2000) {
            saveResults(fileName6, p[i]);
        }

        double rj = countR(delta, i);
        double rj1 = countR(delta, i - 1);

        double vj = countSphere(rj);
        double vj1 = countSphere(rj1);

        double gj = p[i] / (vj - vj1);

        if (n1 < 2000) {
            saveResults(fileName7, gj);
        }
        std::cout << "n[" << i << "] = " << p[i] << std::endl;
        std::cout << "g[" << i << "] = " << gj << std::endl;
    }




    return 0;
}
