//
// Created by Piotr Moszkowicz on 2019-03-06.
//

#pragma once
#include <iostream>
#include <gsl/gsl_math.h>
#include <gsl/gsl_linalg.h>

class Vector {
public:
    explicit Vector(unsigned int size) {
        m_vector = gsl_vector_calloc(size);
        m_size = size;
    }

    double operator[](unsigned int index) const {
        return gsl_vector_get(m_vector, index);
    }

    void operator()(unsigned int index, double value) {
        gsl_vector_set(m_vector, index, value);
    }

    friend std::ostream& operator<<(std::ostream& s, const Vector& v) {
        for(unsigned int i = 0; i < v.m_size; i++) {
            s << "v[" << i << "] = " << (v)[i] << std::endl;
        }
        return s;
    }
private:
    gsl_vector* m_vector;
    unsigned int m_size;
};