#ifndef MATRIX_HPP
#define MATRIX_HPP
#include <vector>
#include "rational.hpp"

template<typename T> class Matrix{
public:
    Matrix();
    Matrix(unsigned int rows, unsigned int cols, const T& value = T());

    T& operator()(unsigned int r, unsigned int c);
    
    void Print();

    void GaussJordan();

private:
    std::vector<std::vector<T> > m_mat;
};

#endif