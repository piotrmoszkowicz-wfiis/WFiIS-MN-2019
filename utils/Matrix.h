//
// Created by Piotr Moszkowicz on 2019-03-07.
//

#pragma once
#include <iostream>

#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>

class Matrix {
public:
    explicit Matrix(unsigned int i, unsigned int j) {
        m_matrix = gsl_matrix_calloc(i, j);
        m_i = i;
        m_j = j;
    }

    double operator()(unsigned int i, unsigned int j) const {
        return gsl_matrix_get(m_matrix, i, j);
    }

    void operator()(unsigned int i, unsigned int j, double value) {
        gsl_matrix_set(m_matrix, i, j, value);
    }

    friend std::ostream& operator<<(std::ostream& s, const Matrix& m) {
        for(unsigned int i = 0; i < m.m_i; i++) {
            for(unsigned int j = 0; j < m.m_j; j++) {
                s << "v[" << i << "][" << j << "] = " << (m)(i, j);
            }
            s << std::endl;
        }
        return s;
    }
private:
    gsl_matrix* m_matrix;
    unsigned int m_i, m_j;
};
