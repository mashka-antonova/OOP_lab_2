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
            data[toIndex(n, m++)] = value;
        ++n;
    }
}

template<typename T>
matrix<T>::~matrix()
{
    delete[] data;
}

template<typename T>
matrix<T>& matrix<T>::operator =(const matrix<T>& mat) {
    if (this != &mat){
        T* newData = new T[mat.rows * mat.cols];
        for (size_t i = 0; i < mat.rows * mat.cols; ++i)
            newData[i] = mat.data[i];
        delete[] data;
        data = newData;
        rows = mat.rows;
        cols = mat.cols;
    }
    return *this;
}

template<typename T>
matrix<T>& matrix<T>::operator +=(const matrix<T>& mat) {
    checkSameSize(mat);
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] += mat.data[i];
    return *this;
}

template<typename T>
matrix<T>& matrix<T>::operator -=(const matrix<T>& mat) {
    checkSameSize(mat);
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] += mat.data[i];
    return *this;
}

template<typename _T>
matrix<_T> operator +(const matrix<_T>& mat1, const matrix<_T>& mat2) {
    matrix<_T> res(mat1);
    res += mat2;
    return res;
}

template<typename _T>
matrix<_T> operator -(const matrix<_T>& mat1, const matrix<_T>& mat2) {
    matrix<_T> res(mat1);
    res -= mat2;
    return res;
}

template<typename _T>
matrix<_T> operator *(const matrix<_T>& mat1, const matrix<_T>& mat2) {
    if (mat1.cols != mat2.rows)
        throw MatrixBaseException("Incorrect matrix sizes for multiplication");

    matrix<_T> result(mat1.rows, mat2.cols);
    for (size_t i = 0; i < mat1.rows; ++i) {
        for (size_t j = 0; j < mat2.cols; ++j) {
            _T sum = _T{};
            for (size_t k = 0; k < mat1.cols; ++k)
                sum += mat1.data[mat1.toIndex(i, k)] * mat2.data[mat2.toIndex(k, j)];
            result.data[result.toIndex(i, j)] = sum;
        }
    }
    return result;
}

template<typename _T>
matrix<_T> operator +(const matrix<_T>& mat, double num) {
    matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] += static_cast<_T>(num);
    return res;
}

template<typename _T>
matrix<_T> operator -(const matrix<_T>& mat, double num) {
    matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] -= static_cast<_T>(num);
    return res;
}

template<typename _T>
matrix<_T> operator /(const matrix<_T>& mat, double num) {
    if (num == 0)
        throw MatrixBaseException("Division by zero");
    matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] /= static_cast<_T>(num);
    return res;
}

template<typename _T>
matrix<_T> operator *(const matrix<_T>& mat, double num) {
    matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] *= static_cast<_T>(num);
    return res;
}

template<typename _T>
std::ostream& operator <<(std::ostream& os, const matrix<_T>& mat) {
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.cols; ++j)
            os << mat.data[mat.toIndex(i, j)] << ' ';
        os << '\n';
    }
    return os;
}

template<typename T>
void matrix<T>::set_elem(unsigned int i, unsigned int j, const T& elem) {
    data[toIndex(i, j)] = elem;
}

template<typename T>
T& matrix<T>::get_elem(unsigned int i, unsigned int j) {
    return data[toIndex(i, j)];
}

template<typename T>
T& matrix<T>::operator ()(unsigned int i, unsigned int j) {
    return get_elem(i, j);
}

template<typename T>
bool matrix<T>::isSquare() {
    return rows == cols;
}

template<typename T>
unsigned int matrix<T>::getCountRows() const{
    return rows;
}

template<typename T>
unsigned int matrix<T>::getCountCols() const{
    return cols;
}

template<typename T>
unsigned int matrix<T>::toIndex(unsigned int i, unsigned int j) const {
    if (i >= rows || j >= cols)
        throw MatrixBaseException("Matrix index out of range");
    return i * cols + j;
}

template<typename T>
void matrix<T>::checkSameSize(const matrix<T> &other) const
{
    if (rows != other.rows || cols != other.cols)
        throw MatrixBaseException("Matrix sizes don't match");
}

#include "iterator.h"
#include "iterator_impl.h"

template<typename T>
Iterator<T> matrix<T>::iteratorBegin() {
    return Iterator<T>(*this, 0);
}

template<typename T>
Iterator<T> matrix<T>::iteratorEnd() {
    return Iterator<T>(*this, rows * cols);
}

#endif // MATRIX_IMPL_H
