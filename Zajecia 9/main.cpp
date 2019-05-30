//
// Created by Piotr Moszkowicz on 2019-05-09.
//

#include <array>
#include <ctime>
#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>

void clearFile(const std::string &fileName) {
    std::ofstream ofs;
    ofs.open(fileName, std::ofstream::out | std::ofstream::trunc);
    ofs.close();
}

void saveToFile(const std::string &fileName, double x, double y, double approx) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << "," << y << "," << approx << "\n";
    file.close();
}

void saveToFile(const std::string &fileName, double x, double y, double approx, double approx2) {
    std::fstream file;
    file.open(fileName, std::ios::app);
    file << x << "," << y << "," << approx << "," << approx2 << "\n";
    file.close();
}

double getAlpha() {
    return (std::rand() % 100) / 100.0 - 0.5;
}

double firstFuncNonAlphaNonWspl(double x) {
    return 2.0 * std::sin(x) + std::sin(2 * x) + 2.0 * std::sin(3 * x);
}

double firstFuncAlphaNonWspl(double x) {
    return 2.0 * std::sin(x) + std::sin(2 * x) + 2.0 * std::sin(3 * x) + getAlpha();
}

double secondFuncNonAlphaNonWspl(double x) {
    return 2.0 * std::sin(x) + std::sin(2 * x) + 2.0 * std::cos(x) + std::cos(2 * x);
}

double thirdFuncNonAlphaNonWspl(double x) {
    return 2.0 * std::sin(1.1 * x) + std::sin(2.1 * x) + 2.0 * std::sin(3.1 * x);
}

template<int ms, int mc>
double getApprox(double x, std::array<double, ms>& wsplA, std::array<double, mc>& wsplB, bool useCos) {
    double a = 0;
    double b = 0;

    for (int i = 1; i <= ms; i++) {
        a += wsplA[i] * std::sin(i * x);
    }

    if (useCos) {
        for (int i = 0; i <= mc; i++) {
            b += wsplB[i] * std::cos(i * x);
        }
    }

    return a + b;
}

double wezel(int i, int n) {
    return ((2.0 * M_PI) / static_cast<double>(n)) * i;
}

int main() {
    std::srand(std::time(nullptr));
    const int n = 100;

    // Pierwsza funkcja
    /* const std::string fileName1 = "data_func_1.csv";
    clearFile(fileName1);

    std::array<double, n> xFirst{};
    std::array<double, n> yFirst{};
    std::array<double, n> approxFirst{};
    std::array<double, 5> wsplA{};
    std::array<double, 5> wsplB{};
    std::array<double, 5> wspl{};
    double alpha = 0;
    std::cout << "Alpha = " << alpha << std::endl;

    for (int i = 0; i < n; i++) {
        xFirst[i] = wezel(i, n);
        yFirst[i] = firstFuncNonAlphaNonWspl(xFirst[i]);

        for (int j = 0; j <= 5; j++) {
            if (j == 0) {
                wsplB[j] += yFirst[i] / (static_cast<double>(n));
            } else {
                wsplA[j] += (yFirst[i] * std::sin(j * xFirst[i])) / (static_cast<double>(n) / 2.0);
                wsplB[j] += (yFirst[i] * std::cos(j * xFirst[i])) / (static_cast<double>(n) / 2.0);
            }
        }
    }

    std::cout << "Wspolczynniki:" << std::endl;

    for (int i = 0; i <= 5; i++) {
        std::cout << i << " A: " << wsplA[i] << " B: " << wsplB[i] << std::endl;
    }

    for (int i = 0; i < n; i++) {
        approxFirst[i] = getApprox<5, 5>(xFirst[i], wsplA, wsplB);
        std::cout << yFirst[i] << " " << approxFirst[i] << std::endl;
        saveToFile(fileName1, xFirst[i], yFirst[i], approxFirst[i]);
    } */

    // Druga funkcja
    /* const std::string fileName2 = "data_func_2.csv";
    clearFile(fileName2);

    std::array<double, n> xSecond{};
    std::array<double, n> ySecond{};
    std::array<double, n> approxSecond{};
    std::array<double, 5> wsplSecondA{};
    std::array<double, 5> wsplSecondB{};
    std::array<double, 5> wsplSecond{};
    double alphaSecond = 0;
    std::cout << "Alpha Second = " << alphaSecond << std::endl;

    for (int i = 0; i < n; i++) {
        xSecond[i] = wezel(i, n);
        ySecond[i] = secondFuncNonAlphaNonWspl(xSecond[i]);

        for (int j = 0; j <= 5; j++) {
            if (j == 0) {
                wsplSecondB[j] += ySecond[i] / (static_cast<double>(n));
            } else {
                wsplSecondA[j] += (ySecond[i] * std::sin(j * xSecond[i])) / (static_cast<double>(n) / 2.0);
                wsplSecondB[j] += (ySecond[i] * std::cos(j * xSecond[i])) / (static_cast<double>(n) / 2.0);
            }
        }
    }

    std::cout << "Wspolczynniki:" << std::endl;

    for (int i = 0; i <= 5; i++) {
        std::cout << i << " A: " << wsplSecondA[i] << " B: " << wsplSecondB[i] << std::endl;
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < n; i++) {
        approxSecond[i] = getApprox<5, 5>(xSecond[i], wsplSecondA, wsplSecondB);
        std::cout << xSecond[i] << " " << ySecond[i] << " " << approxSecond[i] << std::endl;
        saveToFile(fileName2, xSecond[i], ySecond[i], approxSecond[i]);
    } */

    // Trzecia funkcja - 1
    /* const int mc = 0;
    const int ms = 5;
    const std::string fileName3 = "data_func_3.csv";
    clearFile(fileName3);

    std::array<double, n> xThird{};
    std::array<double, n> yThird{};
    std::array<double, n> approxThird{};
    std::array<double, ms> wsplThirdA{};
    std::array<double, mc> wsplThirdB{};

    double alphaThird = 0;
    std::cout << "Alpha Third = " << alphaThird << std::endl;

    for (int i = 0; i < n; i++) {
        xThird[i] = wezel(i, n);
        yThird[i] = thirdFuncNonAlphaNonWspl(xThird[i]);

//        for (int j = 0; j <= mc; j++) {
//            if (j == 0) {
//                wsplThirdB[j] += yThird[i] / (static_cast<double>(n));
//            }
//            wsplThirdB[j] += (yThird[i] * std::cos(j * xThird[i])) / (static_cast<double>(n) / 2.0);
//        }

        for (int j = 1; j <= ms; j++) {
            wsplThirdA[j] += (yThird[i] * std::sin(j * xThird[i])) / (static_cast<double>(n) / 2.0);
        }
    }

    std::cout << "Wspolczynniki:" << std::endl;

    for (int i = 0; i <= ms; i++) {
        std::cout << i << " A: " << wsplThirdA[i] << std::endl;
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < n; i++) {
        approxThird[i] = getApprox<ms, mc>(xThird[i], wsplThirdA, wsplThirdB, false);
        std::cout << xThird[i] << " " << yThird[i] << " " << approxThird[i] << std::endl;
        saveToFile(fileName3, xThird[i], yThird[i], approxThird[i]);
    }

    // Trzecia funkcja - 2
    const int mc2 = 5;
    const int ms2 = 5;
    const std::string fileName4 = "data_func_3_2.csv";
    clearFile(fileName4);

    std::array<double, n> xThird2{};
    std::array<double, n> yThird2{};
    std::array<double, n> approxThird2{};
    std::array<double, ms2> wsplThird2A{};
    std::array<double, mc2> wsplThird2B{};

    double alphaThird2 = 0;
    std::cout << "Alpha Third2 = " << alphaThird2 << std::endl;

    for (int i = 0; i < n; i++) {
        xThird2[i] = wezel(i, n);
        yThird2[i] = thirdFuncNonAlphaNonWspl(xThird2[i]);

        for (int j = 0; j <= mc2; j++) {
            if (j == 0) {
                wsplThird2B[j] += yThird2[i] / (static_cast<double>(n));
            }
            wsplThird2B[j] += (yThird2[i] * std::cos(j * xThird2[i])) / (static_cast<double>(n) / 2.0);
        }

        for (int j = 1; j <= ms2; j++) {
            wsplThird2A[j] += (yThird2[i] * std::sin(j * xThird2[i])) / (static_cast<double>(n) / 2.0);
        }
    }

    std::cout << "Wspolczynniki:" << std::endl;

    for (int i = 0; i <= 5; i++) {
        std::cout << i << " A: " << wsplThird2A[i] << " B: " << wsplThird2B[i] << std::endl;
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < n; i++) {
        approxThird2[i] = getApprox<ms2, mc2>(xThird2[i], wsplThird2A, wsplThird2B, true);
        std::cout << xThird2[i] << " " << yThird2[i] << " " << approxThird2[i] << std::endl;
        saveToFile(fileName4, xThird2[i], yThird2[i], approxThird2[i]);
    }

    // Trzecia funkcja - 3
    const int mc3 = 10;
    const int ms3 = 10;
    const std::string fileName5 = "data_func_3_3.csv";
    clearFile(fileName5);

    std::array<double, n> xThird3{};
    std::array<double, n> yThird3{};
    std::array<double, n> approxThird3{};
    std::array<double, ms3> wsplThird3A{};
    std::array<double, mc3> wsplThird3B{};

    double alphaThird3 = 0;
    std::cout << "Alpha Third3 = " << alphaThird3 << std::endl;

    for (int i = 0; i < n; i++) {
        xThird3[i] = wezel(i, n);
        yThird3[i] = thirdFuncNonAlphaNonWspl(xThird3[i]);

        for (int j = 0; j <= mc3; j++) {
            if (j == 0) {
                wsplThird3B[j] += yThird3[i] / (static_cast<double>(n));
            }
            wsplThird3B[j] += (yThird3[i] * std::cos(j * xThird3[i])) / (static_cast<double>(n) / 2.0);
        }

        for (int j = 1; j <= ms3; j++) {
            wsplThird3A[j] += (yThird3[i] * std::sin(j * xThird3[i])) / (static_cast<double>(n) / 2.0);
        }
    }

    std::cout << "Wspolczynniki:" << std::endl;

    for (int i = 0; i <= 10; i++) {
        std::cout << i << " A: " << wsplThird3A[i] << " B: " << wsplThird3B[i] << std::endl;
    }

    std::cout << std::endl << std::endl;

    for (int i = 0; i < n; i++) {
        approxThird3[i] = getApprox<ms3, mc3>(xThird3[i], wsplThird3A, wsplThird3B, true);
        std::cout << xThird3[i] << " " << yThird3[i] << " " << approxThird3[i] << std::endl;
        saveToFile(fileName5, xThird3[i], yThird3[i], approxThird3[i]);
    } */

    // Pierwsza funckja z alpha
    const std::string fileName1 = "data_func_1_alpha.csv";
    clearFile(fileName1);

    std::array<double, n> xFirst{};
    std::array<double, n> yFirst{};
    std::array<double, n> approxFirst{};
    std::array<double, n> approxFirst2{};
    std::array<double, 5> wsplA{};
    std::array<double, 5> wsplB{};

    std::array<double, 30> wsplA_2{};
    std::array<double, 30> wsplB_2{};


    for (int i = 0; i < n; i++) {
        xFirst[i] = wezel(i, n);
        yFirst[i] = firstFuncAlphaNonWspl(xFirst[i]);

        for (int j = 0; j <= 5; j++) {
            if (j == 0) {
                wsplB[j] += yFirst[i] / (static_cast<double>(n));
            } else {
                wsplA[j] += (yFirst[i] * std::sin(j * xFirst[i])) / (static_cast<double>(n) / 2.0);
                wsplB[j] += (yFirst[i] * std::cos(j * xFirst[i])) / (static_cast<double>(n) / 2.0);
            }
        }

        for (int j = 0; j <= 30; j++) {
            if (j == 0) {
                wsplB_2[j] += yFirst[i] / (static_cast<double>(n));
            } else {
                wsplA_2[j] += (yFirst[i] * std::sin(j * xFirst[i])) / (static_cast<double>(n) / 2.0);
                wsplB_2[j] += (yFirst[i] * std::cos(j * xFirst[i])) / (static_cast<double>(n) / 2.0);
            }
        }
    }

    std::cout << "Wspolczynniki:" << std::endl;

    for (int i = 0; i <= 5; i++) {
        std::cout << i << " A: " << wsplA[i] << " B: " << wsplB[i] << std::endl;
    }

    for (int i = 0; i <= 30; i++) {
        std::cout << i << " A: " << wsplA_2[i] << " B: " << wsplB_2[i] << std::endl;
    }

    for (int i = 0; i < n; i++) {
        approxFirst[i] = getApprox<5, 5>(xFirst[i], wsplA, wsplB, true);
        approxFirst2[i] = getApprox<30, 30>(xFirst[i], wsplA_2, wsplB_2, true);
        std::cout << yFirst[i] << " " << approxFirst[i] << " " << approxFirst2[i] << std::endl;
        saveToFile(fileName1, xFirst[i], yFirst[i], approxFirst[i], approxFirst2[i]);
    }

    return 0;
}