//
// Created by Piotr Moszkowicz on 2019-03-06.
//

#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>

#include "Matrix.h"
#include "Vector.h"

void
saveNeededStuffToFile(std::string &fileName, unsigned int iterationNumber, double alfaK, double normRest,
                      double normSolv) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << "Numer iteracji: " << iterationNumber << std::endl;
    file << "AlfaK: " << alfaK << std::endl;
    file << "Wartosc normy wektora reszt: " << normRest << " Wartosc normy wektor rozwiazan: " << normSolv << std::endl
         << std::endl;
    file.close();
}

double countNorm(double rkt, double rk) {
    return sqrt(rkt * rk);
}

int main() {
    const unsigned int n = 1000;

    auto matrix = new Matrix(n, n);
    auto b = new Vector(n);
    auto x = new Vector(n);

    for (unsigned int i = 0; i < n; i++) {
        for (unsigned int j = 0; j < n; j++) {
            auto val = std::abs(static_cast<double>(i) - static_cast<double>(j));

            if (val <= 5) {
                (*matrix)(i, j, (1.0 / (1.0 + val)));
            } else {
                (*matrix)(i, j, 0.0);
            }
        }
    }

    for (unsigned int i = 0; i < n; i++) {
        (*b)(i, (static_cast<double>(i) + 1));
        (*x)(i, 0.0);
    }

    return 0;
}