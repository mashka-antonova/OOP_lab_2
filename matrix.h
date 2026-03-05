#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <utility>
#include "matrix_base_exception.h"
#include "matrix_index_exception.h"

template <typename T>
class matrix
{
private:
    unsigned int rows;
    unsigned int cols;
    T* data;

    unsigned int to_index(unsigned int i, unsigned int j) const;
    void check_same_size(const matrix<T> &other) const;

public:
    matrix(unsigned int n, unsigned int m);
    matrix(const matrix<T>& mat);
    matrix(matrix<T>&& mat) noexcept;
    explicit matrix(std::initializer_list<std::initializer_list<T>> list);
    ~matrix();

};

#include "matrix_impl.h"
#endif // MATRIX_H
