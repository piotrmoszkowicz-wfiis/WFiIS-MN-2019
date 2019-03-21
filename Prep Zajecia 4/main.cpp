//
// Created by Piotr Moszkowicz on 2019-03-21.
//
#include <iostream>
#include <cmath>

#include "/usr/local/opt/NR/nrutil.h"
#include "/usr/local/opt/NR/nrutil.c"
#include "/usr/local/opt/NR/gaussj.c"

#define N 3 // rozmiar macierzy A: NxN

int main(void) {
    float **A,**b;
//	Alokacja macierzy
    A = matrix(1, N, 1, N);
    b = matrix(1, N, 1, 1);

// 	Wypelnienie macierzy A i wektora b
    for(int i=1; i<=N; ++i){
        b[i][1] = 0.0;
        for(int j=1; j<=N; ++j)
            A[i][j] = 0.0;
    }
    b[1][1] = -4.0;
    b[2][1] = 9.0;
    b[3][1] = -16.0;

    A[1][1] = 2.0; A[1][2] = 3.0; A[1][3] = 0.0;
    A[2][1] = -1.0; A[2][2] = 1.0; A[2][3] = 4.0;
    A[3][1] = 3.0; A[3][2] = 11.0; A[3][3] = 1.0;

//	Rozwiazanie ukladu rownan Ax=b - wywolanie procedury:
    gaussj(A,N,b,1);

//	Wypisanie rozwiazania, ktore procedura gaussj(A,N,b,1); zapisala w wektorze b.
    for(int i=1; i<=N; ++i)
        std::cout << b[i][1] << std::endl;

//	Zwolnienie pamieci
    free_matrix(A,1,N,1,N);
    free_matrix(b,1,N,1,1);

    return 0;
}