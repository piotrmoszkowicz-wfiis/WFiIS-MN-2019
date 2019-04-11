//
// Created by Piotr Moszkowicz on 2019-04-04.
//

#include <array>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <fstream>

void clearFile(std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveToFile(std::string &fileName, int i, double fx, double x, double e, double p, bool shouldP) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << std::fixed << std::setw(20) << std::setprecision(15) << static_cast<double>(i) << "," << fx << "," << x
         << "," << e;
    if (shouldP) {
        file << "," << p << std::endl;
    } else {
        file << std::endl;
    }
    file.close();
}

void
saveToFileWithDer(std::string &fileName, int i, double fx, double fxd, double x, double e, double p, bool shouldP) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << std::fixed << std::setw(20) << std::setprecision(15) << static_cast<double>(i) << "," << fx << "," << fxd
         << "," << x << "," << e;
    if (shouldP) {
        file << "," << p << std::endl;
    } else {
        file << std::endl;
    }
    file.close();
}

double logarFunc(double x) {
    return std::pow((std::log(x) - x), 6) - 1;
}

double logarDerFunc(double x) {
    return 6 * std::pow((std::log(x) - x), 5) * ((1 / x) - 1);
}

double normFunc(double x) {
    return (x * x * x) + 2 * (x * x) - (3 * x) + 4;
}

double normDerFunc(double x) {
    return 3 * (x * x) + (2 * x) - 3;
}

double epsiValue(double xk, double xd) {
    return std::abs(xk - xd);
}

double zbieznosc(double ek, double ekPrev, double ekPrevPrev) {
    return std::log(ekPrev / ek) / std::log(ekPrevPrev / ekPrev);
}

void metodaSiecznych(double xd, double xm1, double x0, int n, double func(double), std::string &fileName) {
    std::array<double, 22> x = {};
    std::array<double, 22> epsi = {};
    std::array<double, 22> zbieznosci = {};

    x[0] = xm1;
    x[1] = x0;

    epsi[0] = epsiValue(x[0], xd);
    epsi[1] = epsiValue(x[1], xd);

    for (int i = 2; i < n; i++) {
        double xPrevPrev = func(x[i - 2]);
        double xPrev = func(x[i - 1]);
        x[i] = x[i - 1] - ((xPrev * (x[i - 1] - x[i - 2])) / (xPrev - xPrevPrev));
        epsi[i] = epsiValue(x[i], xd);
        zbieznosci[i] = zbieznosc(epsi[i], epsi[i - 1], epsi[i - 2]);
        saveToFile(fileName, i - 1, xPrev, x[i - 1], epsi[i], zbieznosci[i], true);
    }
}

void metodaNewtona(double xd, double x0, int n, double func(double), double funcDer(double), std::string &fileName) {
    std::array<double, 21> x = {};
    std::array<double, 21> epsi = {};
    std::array<double, 21> zbieznosci = {};

    x[0] = x0;

    epsi[0] = epsiValue(x[0], xd);

    for (int i = 1; i < n; i++) {
        x[i] = x[i - 1] - (func(x[i - 1]) / funcDer(x[i - 1]));
        epsi[i] = epsiValue(x[i], xd);

        if (i != 1) {
            zbieznosci[i] = zbieznosc(epsi[i], epsi[i - 1], epsi[i - 2]);
        }
        saveToFileWithDer(fileName, i, func(x[i - 1]), funcDer(x[i - 1]), x[i - 1], epsi[i], zbieznosci[i], i != 1);
        // 20 iteracji to będzie dużo opisać to w sprawku, bo jakieś tarapaty są jak za dużo -> to wynika z wyników
    }
}

int main() {
    int n = 22;
    double xd = 1.0;
    double xd2 = -3.284277537306950;

    std::string fileNameSieczneLog = "data_sieczne_log.csv";
    std::string fileNameSieczneRown = "data_sieczne_rown.csv";
    std::string fileNameNewtonLog = "data_newton_log.csv";
    std::string fileNameNewtonRown = "data_newton_rown.csv";

    clearFile(fileNameSieczneLog);
    clearFile(fileNameSieczneRown);
    clearFile(fileNameNewtonLog);
    clearFile(fileNameNewtonRown);

    // Funkcja pierwsza
    metodaSiecznych(xd, 3.01, 3.0, n, logarFunc, fileNameSieczneLog);
    std::cout << std::endl << std::endl << std::endl;
    metodaNewtona(xd, 3.0, n - 1, logarFunc, logarDerFunc, fileNameNewtonLog);

    //Funkcja druga
    metodaSiecznych(xd2, -20.1, -20, n, normFunc, fileNameSieczneRown);
    std::cout << std::endl << std::endl << std::endl;
    metodaNewtona(xd2, -20.0, n - 1, normFunc, normDerFunc, fileNameNewtonRown);
    return 0;
}