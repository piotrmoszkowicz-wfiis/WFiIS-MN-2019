//
// Created by Piotr Moszkowicz on 2019-05-30.
//

#include <ctime>
#include <cmath>
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>

#include <gsl/gsl_errno.h>
#include <gsl/gsl_fft_complex.h>

double getDelta() {
    return (std::rand() % 100) / 100.0 - 0.5;
}

double g(double t, double sigma) {
    return (1.0 / (sigma * std::sqrt(2.0 * M_PI))) * std::exp(-1.0 * ((t * t) / (2.0 * (sigma * sigma))));
}

double f0(double t, double T) {
    double omega = (2.0 * M_PI) / T;

    return std::sin(omega * t) + std::sin(2 * omega * t) + std::sin(3 * omega * t);
}

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveToFile(const std::string &fileName, double t, double f0, double f, double spl) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << t << "," << f0 << "," << f << "," << spl << "\n";
    file.close();
}

int main() {
    std::srand(std::time(nullptr));

    int k[3] = {8, 10, 12};
    double T = 1.0;
    double Tmax = 3.0 * T;
    double sigma = T / 20.0;

    for (auto kNext : k) {
        int n = static_cast<int>(std::pow(2, kNext));
        double f[2 * n], fCpy[2 * n], fCpyZ[2 * n], g1[2 * n], g2[2 * n];

        std::string fileName = "data_zaj11_" + std::to_string(kNext) + ".csv";

        clearFile(fileName);

        for (int i = 0; i < n; i++) {
            int j = 2 * i;
            double dt = Tmax / n;
            f[j] = f0(dt * i, T);
            fCpy[j] = f[j];
            f[j] += getDelta();
            fCpyZ[j] = f[j];
            g1[j] = g(dt * i, sigma);
            g2[j] = g1[j];


            j = 2 * i + 1;
            f[j] = 0;
            fCpy[j] = f[j];
            fCpyZ[j] = f[j];
            g1[j] = 0;
            g2[j] = g1[j];
        }

        gsl_fft_complex_radix2_forward(f, 1, n);
        gsl_fft_complex_radix2_forward(g1, 1, n);
        gsl_fft_complex_radix2_backward(g2, 1, n);

        for (int i = 0; i < n; i++) {
            double a1 = f[2 * i];
            double b1 = f[(2 * i) + 1];

            double a2 = g1[2 * i] + g2[2 * i];
            double b2 = g1[(2 * i) + 1] + g2[(2 * i) + 1];

            f[2 * i] = a1 * a2 - b1 * b2;
            f[(2 * i) + 1] = a1 * b2 + a2 * b1;
        }

        gsl_fft_complex_radix2_backward(f, 1, n);

        double fMax = 0.0;

        for (int i = 0; i < n; i++) {
            int j = 2 * i;
            double fMaxTemp = std::abs(f[j]);

            if (fMaxTemp > fMax) {
                fMax = fMaxTemp;
            }
        }

        for (int i = 0; i < n; i++) {
            int j = 2 * i;
            double spl = (f[j] * 2.5) / fMax;
            double dt = Tmax / n;
            saveToFile(fileName, dt * i, fCpy[j], fCpyZ[j], spl);
        }
    }

    return 0;
}