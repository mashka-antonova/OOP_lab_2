#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <utility>
#include "matrix_base_exception.h"

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

    void setElem(unsigned int i, unsigned int j,const T& elem);
    T& getElem(unsigned int i, unsigned int j);
    T& operator ()(unsigned int i, unsigned int j);
    bool isSquare();
    unsigned int getCountRows() const;
    unsigned int getCountCols() const;

    Iterator<T> iteratorBegin();
    Iterator<T> iteratorEnd();
};

#include "matrix_impl.h"
#endif // MATRIX_H
