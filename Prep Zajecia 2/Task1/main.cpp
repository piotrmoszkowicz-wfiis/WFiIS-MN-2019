//
// Created by Piotr Moszkowicz on 2019-03-06.
//

#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>

#include "Vector.h"

void copyDoubleArray(double* a1, const double* a2, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        a1[i] = a2[i];
    }
}

void saveNeededStuffToFile(std::string& fileName, double* array, unsigned int size) {
    std::fstream file;
    file.open(fileName, std::ios::out);
    for(unsigned int i = 0; i < size; i++) {
        file << array[i] << ",";
    }
    file.close();
}

int main() {
    std::string fileName = "data_0.csv";
    const double v0 = 0.0;
    const double littleOmega = 1.0;
    const double h = 0.02;

    const unsigned int n = 1000;

    const double beta = 0.4;
    const double force = 0.1;
    const double omega = 0.8;

    const double a1 = 1.0;
    const double a2 = (littleOmega * littleOmega) * (h * h) - 2.0 - (beta * h);
    const double a3 = 1.0 + (beta * h);

    double b[1000] = {0.0};
    double xs[1000] = {1.0};
    double xn[1000] = {1.0};

    auto d0 = new Vector(1000);
    auto d1 = new Vector(1000);
    auto d2 = new Vector(1000);

    (*d0)(0, 1.0);
    (*d0)(1, 1.0);

    (*d1)(0, 0.0);
    (*d1)(1, -1.0);

    (*d2)(0, 0.0);
    (*d2)(1, 0.0);

    b[0] = 1.0;
    b[1] = 0.0;

    for(unsigned int i = 2; i < n; i++) {
        (*d0)(i, a3);
        (*d1)(i, a2);
        (*d2)(i, a1);

        b[i] = force * sin(omega * h * i) * (h * h);
    }

    for(unsigned int j = 0; j < 1000; j++) {
        for(unsigned int i = 0; i < n; i++) {
            double firstXSValue = 1.0;
            double secondXSValue = 1.0;
            if (i > 2) {
                firstXSValue = xs[i - 1];
                secondXSValue = xs[i - 2];
            }
            xn[i] = (1.0 / (*d0)[i]) * (b[i] - (*d1)[i] * firstXSValue - (*d2)[i] * secondXSValue);
            std::cout << xn[i] << std::endl;
        }
        copyDoubleArray(xs, xn, 1000);
    }
    saveNeededStuffToFile(fileName, xn, 1000);

    return 0;
}