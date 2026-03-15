#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include "matrix_base_exception.h"
#include "iterator.h"

template<typename T>
class Iterator;

template <typename T>
class Matrix
{
private:
    unsigned int rows;
    unsigned int cols;
    T* data;

    unsigned int toIndex(unsigned int i, unsigned int j) const;
    void checkSameSize(const Matrix<T> &other) const;

    template<typename>
    friend class Iterator;

public:
    Matrix(unsigned int n, unsigned int m);
    Matrix(const Matrix<T>& mat);
    Matrix(Matrix<T>&& mat) noexcept;
    explicit Matrix(std::initializer_list<std::initializer_list<T>> list);
    ~Matrix();

    Matrix<T>& operator =(const Matrix<T>& mat);
    Matrix<T>& operator +=(const Matrix<T>& mat);
    Matrix<T>& operator -=(const Matrix<T>& mat);

    template <typename _T>
    friend Matrix<_T> operator +(const Matrix<_T>& mat1, const Matrix<_T>& mat2);

    template <typename _T>
    friend Matrix<_T> operator -(const Matrix<_T>& mat1, const Matrix<_T>& mat2);

    template <typename _T>
    friend Matrix<_T> operator *(const Matrix<_T>& mat1, const Matrix<_T>& mat2);

    template <typename _T>
    friend Matrix<_T> operator +(const Matrix<_T>& m1, double num);

    template <typename _T>
    friend Matrix<_T> operator -(const Matrix<_T>& m1, double num);

    template <typename _T>
    friend Matrix<_T> operator /(const Matrix<_T>& m1, double num);

    template <typename _T>
    friend Matrix<_T> operator *(const Matrix<_T>& m1, double num);

    template<typename _T>
    friend std::ostream& operator <<(std::ostream& os, const Matrix<_T>& mat);

    void setElem(unsigned int i, unsigned int j, const T& elem);
    T& getElem(unsigned int i, unsigned int j);
    T& operator ()(unsigned int i, unsigned int j);
    bool isSquare();
    unsigned int getCountRows() const;
    unsigned int getCountCols() const;

    Iterator<T> iteratorBegin();
    Iterator<T> iteratorEnd();
};

template<typename T>
Matrix<T>::Matrix(unsigned int n, unsigned int m)
    : rows(n), cols(m), data(new T[n * m]{}) {}

template<typename T>
Matrix<T>::Matrix(const Matrix<T>& mat)
    : rows(mat.rows), cols(mat.cols), data(new T[rows * cols]{})
{
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] = mat.data[i];
}

template<typename T>
Matrix<T>::Matrix(Matrix<T>&& mat) noexcept
    : rows(mat.rows), cols(mat.cols), data(mat.data)
{
    mat.rows = 0;
    mat.cols = 0;
    mat.data = nullptr;
}

template<typename T>
Matrix<T>::Matrix(std::initializer_list<std::initializer_list<T>> list)
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
Matrix<T>::~Matrix()
{
    delete[] data;
}

template<typename T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T>& mat) {
    if (this != &mat) {
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
Matrix<T>& Matrix<T>::operator +=(const Matrix<T>& mat) {
    checkSameSize(mat);
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] += mat.data[i];
    return *this;
}

template<typename T>
Matrix<T>& Matrix<T>::operator -=(const Matrix<T>& mat) {
    checkSameSize(mat);
    for (size_t i = 0; i < rows * cols; ++i)
        data[i] -= mat.data[i];
    return *this;
}

template <typename _T>
Matrix<_T> operator +(const Matrix<_T>& mat1, const Matrix<_T>& mat2) {
    Matrix<_T> res(mat1);
    res += mat2;
    return res;
}

template <typename _T>
Matrix<_T> operator -(const Matrix<_T>& mat1, const Matrix<_T>& mat2) {
    Matrix<_T> res(mat1);
    res -= mat2;
    return res;
}

template <typename _T>
Matrix<_T> operator *(const Matrix<_T>& mat1, const Matrix<_T>& mat2) {
    if (mat1.cols != mat2.rows)
        throw MatrixBaseException("Incorrect matrix sizes for multiplication");

    Matrix<_T> result(mat1.rows, mat2.cols);
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

template <typename _T>
Matrix<_T> operator +(const Matrix<_T>& mat, double num) {
    Matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] += static_cast<_T>(num);
    return res;
}

template <typename _T>
Matrix<_T> operator -(const Matrix<_T>& mat, double num) {
    Matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] -= static_cast<_T>(num);
    return res;
}

template <typename _T>
Matrix<_T> operator /(const Matrix<_T>& mat, double num) {
    if (num == 0)
        throw MatrixBaseException("Division by zero");
    Matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] /= static_cast<_T>(num);
    return res;
}

template <typename _T>
Matrix<_T> operator *(const Matrix<_T>& mat, double num) {
    Matrix<_T> res(mat);
    for (size_t i = 0; i < mat.rows * mat.cols; ++i)
        res.data[i] *= static_cast<_T>(num);
    return res;
}

template<typename _T>
std::ostream& operator <<(std::ostream& os, const Matrix<_T>& mat) {
    for (size_t i = 0; i < mat.rows; ++i) {
        for (size_t j = 0; j < mat.cols; ++j)
            os << mat.data[mat.toIndex(i, j)] << ' ';
        os << '\n';
    }
    return os;
}

template<typename T>
void Matrix<T>::setElem(unsigned int i, unsigned int j, const T& elem) {
    data[toIndex(i, j)] = elem;
}

template<typename T>
T& Matrix<T>::getElem(unsigned int i, unsigned int j) {
    return data[toIndex(i, j)];
}

template<typename T>
T& Matrix<T>::operator ()(unsigned int i, unsigned int j) {
    return getElem(i, j);
}

template<typename T>
bool Matrix<T>::isSquare() {
    return rows == cols;
}

template<typename T>
unsigned int Matrix<T>::getCountRows() const {
    return rows;
}

template<typename T>
unsigned int Matrix<T>::getCountCols() const {
    return cols;
}

template<typename T>
unsigned int Matrix<T>::toIndex(unsigned int i, unsigned int j) const {
    if (i >= rows || j >= cols)
        throw MatrixBaseException("Matrix index out of range");
    return i * cols + j;
}

template<typename T>
void Matrix<T>::checkSameSize(const Matrix<T> &other) const {
    if (rows != other.rows || cols != other.cols)
        throw MatrixBaseException("Matrix sizes don't match");
}

template<typename T>
Iterator<T> Matrix<T>::iteratorBegin() {
    return Iterator<T>(*this, 0);
}

template<typename T>
Iterator<T> Matrix<T>::iteratorEnd() {
    return Iterator<T>(*this, rows * cols);
}

#endif // MATRIX_H
