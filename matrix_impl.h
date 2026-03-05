#ifndef MATRIX_IMPL_H
#define MATRIX_IMPL_H

#include "matrix.h"
#include <initializer_list>
#include <iostream>
#include <utility>
#include "matrix_base_exception.h"
#include "matrix_index_exception.h"

template <typename T>
matrix<T>::matrix(unsigned int n, unsigned int m)
    : rows(n), cols(m), data(new T[n * m]{}) {}

template <typename T>
matrix<T>::matrix(const matrix<T>& mat)
    : rows(mat.rows), cols(mat.cols), data(new T[rows * cols]{})
{
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] = mat.data[i];
}

template <typename T>
matrix<T>::matrix(matrix<T>&& mat) noexcept
    : rows(mat.rows), cols(mat.cols), data(mat.data)
{
    mat.rows = 0;
    mat.cols = 0;
    mat.data = nullptr;
}

template <typename T>
matrix<T>::matrix(std::initializer_list<std::initializer_list<T>> list)
    : rows(list.size()), cols(0), data(nullptr)
{
    if (rows == 0)
        throw MatrixBaseException("Initializer list for matrix can't be empty");

    cols = list.begin()->size();
    if (cols == 0)
        throw MatrixBaseException("Matrix must have at least one column");

    data = new T[rows * cols]{};
    size_t n = 0;
    for (const auto& row : list) {
        if (row.size() != cols)
            throw MatrixBaseException("All rows in initializer list must have same size");
        size_t m = 0;
        for (const auto& value : row)
            data[to_index(n, m++)] = value;
        ++n;
    }
}

template<typename T>
matrix<T>::~matrix()
{
    delete[] data;
}



template<typename T>
unsigned int matrix<T>::to_index(unsigned int i, unsigned int j) const {
    if (i >= rows || j >= cols)
        throw MatrixIndexException("Matrix index out of range");
    return i * cols + j;
}

template<typename T>
void matrix<T>::check_same_size(const matrix<T> &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw MatrixBaseException("Matrix sizes do not match");
}

#endif // MATRIX_IMPL_H
