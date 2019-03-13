//
// Created by Piotr Moszkowicz on 2019-03-07.
//

#include <iostream>
#include <fstream>

#include "Vector.h"

void saveNeededStuffToFile(std::string &fileName, Vector *vVector, const double *h, unsigned int size) {
    std::fstream file;
    file.open(fileName, std::ios::out);

    for (unsigned int i = 1; i < size + 1; i++) {
        file << i * (*h) - 2 << "," << (*vVector)[i] << std::endl;
    }

    file.close();
}

int main() {
    const unsigned int n = 500;
    std::string fileName = "data.csv";

    auto aVector = new Vector(n + 1);
    auto bVector = new Vector(n + 1);
    auto cVector = new Vector(n + 1);
    auto dVector = new Vector(n + 1);
    auto lVector = new Vector(n + 1);
    auto uVector = new Vector(n + 1);
    auto vVector = new Vector(n + 1);
    auto yVector = new Vector(n + 1);
    auto xVector = new Vector(n + 1);

    const double xa = 0.5;
    const double xb = 2;

    const double h = (2.0 * xb) / (n - 1);

    (*dVector)(1, 1.0);
    (*cVector)(1, 0.0);
    (*bVector)(1, 0.0);

    for (unsigned int i = 1; i < n + 1; i++) {
        if (i != 1) {
            (*aVector)(i, 1.0 / (h * h));
            (*cVector)(i, 1.0 / (h * h));
            (*dVector)(i, -2.0 / (h * h));
        }

        (*xVector)(i, -xb + (h * (i - 1)));

        if (i != 1) {
            const double xVectorValue = (*xVector)[i];
            double setB = 0.0;

            if (xVectorValue >= -xb && xVectorValue < -xa) {
                setB = 0.0;
            } else if (xVectorValue >= -xa && xVectorValue < 0) {
                setB = -1.0;
            } else if (xVectorValue == 0) {
                setB = 0.0;
            } else if (xVectorValue > 0 && xVectorValue <= xa) {
                setB = 1.0;
            } else if (xVectorValue > xa && xVectorValue <= xb) {
                setB = 0.0;
            }

            (*bVector)(i, setB);
        }
    }

    (*aVector)(n, 0.0);
    (*dVector)(n, 1.0);
    (*bVector)(n, 0.0);

    (*uVector)(1, (*dVector)[1]);

    for (unsigned int i = 2; i < n + 1; i++) {
        const double lValue = (*aVector)[i] / (*uVector)[i - 1];
        const double uValue = (*dVector)[i] - (lValue * (*cVector)[i - 1]);
        (*lVector)(i, lValue);
        (*uVector)(i, uValue);
    }

    (*yVector)(1, (*bVector)[1]);


    for (unsigned int i = 2; i < n + 1; i++) {
        const double yValue = (*bVector)[i] - ((*lVector)[i] * (*yVector)[i - 1]);
        (*yVector)(i, yValue);
    }

    (*vVector)(n, (*yVector)[n] / (*uVector)[n]);

    for (unsigned int i = n - 1; i >= 1; i--) {
        const double vValue = ((*yVector)[i] - ((*cVector)[i] * (*vVector)[i + 1])) / (*uVector)[i];
        (*vVector)(i, vValue);
    }

    saveNeededStuffToFile(fileName, vVector, &h, n);

    return 0;
}
