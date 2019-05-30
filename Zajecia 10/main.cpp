//
// Created by Piotr Moszkowicz on 2019-05-16.
//

#include <cmath>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <string>

double r() {
    return (std::sqrt(5) - 1.0) / 2.0;
}

double lambda1() {
    return r() * r();
}

double lambda2() {
    return r();
}

double x1Value(double xa, double xb) {
    return xa + lambda1() * (xb - xa);
}

double x2Value(double xa, double xb) {
    return xa + lambda2() * (xb - xa);
}

double x1StaticLambda(double xa, double xb) {
    return xa + (1.0/3.0) * (xb - xa);
}

double x2StaticLambda(double xa, double xb) {
    return xa + (2.0/3.0) * (xb - xa);
}

double func1(double x) {
    return std::log(std::pow(x, 5) + 3 * (x * x) + x + 9);
}

double func2(double x) {
    return std::pow(x, 6);
}

double xmin(double x1, double x2) {
    return (x1 + x2) / 2.0;
}

double shallEndValue(double x1, double x2) {
    return std::abs(x1 - x2);
}

bool shallEnd(double x1, double x2, double epsi) {
    return std::abs(x1 - x2) < epsi;
}

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveToFile(const std::string &fileName, int i, double diff) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << i << "," << std::setprecision(10) << diff << "\n";
    file.close();
}

double findMin(double xa, double xb, double epsilon, int* i, double (*func)(double), std::string& fileName, double xDokl, bool useLambdaExpr) {
    double x1 = xa;
    double x2 = xb;

    while(!shallEnd(x1, x2, epsilon)) {
        (*i)++;
        double f1 = func(x1);
        double f2 = func(x2);

        if (f2 > f1) {
            if (useLambdaExpr) {
                x2 = x2Value(x1, x2);
            } else {
                x2 = x2StaticLambda(x1, x2);
            }
        } else {
            if (useLambdaExpr) {
                x1 = x1Value(x1, x2);
            } else {
                x1 = x1StaticLambda(x1, x2);
            }
        }

        saveToFile(fileName, *i, std::abs(xmin(x1, x2) - xDokl));
    }

    return xmin(x1, x2);
}

int main() {
    double epsilon = std::pow(10, -6);
    // Podpunkt 2
    double xa1 = -0.5;
    double xb1 = 1.0;

    double xDokldane = -0.1673198;

    int numOfIter1 = 0;
    std::string fileName1 = "data_func1_zloty.csv";

    clearFile(fileName1);

    double minX1 = findMin(xa1, xb1, epsilon, &numOfIter1, func1, fileName1, xDokldane, true);
    std::cout << "MinX1: " << minX1 << "Iteracje: " << numOfIter1 << std::endl;

    int numOfIter2 = 0;
    std::string fileName2 = "data_func1_jednatrzecia.csv";

    clearFile(fileName2);

    double minX2 = findMin(xa1, xb1, epsilon, &numOfIter2, func1, fileName2, xDokldane, false);
    std::cout << "MinX2: " << minX2 << "Iteracje: " << numOfIter2 << std::endl;

    ///------//

    // Podunkt 5
    double xa2 = -4.0;
    double xb2 = 1.0;

    double xDokladne2 = 0;

    int numOfIter3 = 0;
    std::string fileName3 = "data_func2_zloty.csv";

    clearFile(fileName3);

    double minX3 = findMin(xa2, xb2, epsilon, &numOfIter3, func2, fileName3, xDokladne2, true);
    std::cout << "MinX3: " << minX3 << "Iteracje: " << numOfIter3 << std::endl;

    int numOfIter4 = 0;
    std::string fileName4 = "data_func2_jednatrzecia.csv";

    clearFile(fileName4);

    double minX4 = findMin(xa2, xb2, epsilon, &numOfIter4, func2, fileName4, xDokladne2, false);
    std::cout << "MinX4: " << minX4 << "Iteracje: " << numOfIter4 << std::endl;


    return 0;
}