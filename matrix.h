#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <iostream>
#include <utility>
#include "matrix_base_exception.h"

template<typename T>
class Iterator;

template <typename T>
class matrix
{
private:
    unsigned int rows;
    unsigned int cols;
    T* data;

    unsigned int toIndex(unsigned int i, unsigned int j) const;
    void checkSameSize(const matrix<T> &other) const;

    template<typename>
    friend class Iterator;

public:
    matrix(unsigned int n, unsigned int m);
    matrix(const matrix<T>& mat);
    matrix(matrix<T>&& mat) noexcept;
    explicit matrix(std::initializer_list<std::initializer_list<T>> list);
    ~matrix();

    matrix<T>& operator =(const matrix<T>& mat);
    matrix<T>& operator +=(const matrix<T>& mat);
    matrix<T>& operator -=(const matrix<T>& mat);

    template <typename _T>
    friend matrix<_T> operator +(const matrix<_T>& mat1, const matrix<_T>& mat2);

    template <typename _T>
    friend matrix<_T> operator -(const matrix<_T>& mat1, const matrix<_T>& mat2);

    template <typename _T>
    friend matrix<_T> operator *(const matrix<_T>& mat1, const matrix<_T>& mat2);

    template <typename _T>
    friend matrix<_T> operator +(const matrix<_T>& m1, double num);

    template <typename _T>
    friend matrix<_T> operator -(const matrix<_T>& m1, double num);

    template <typename _T>
    friend matrix<_T> operator /(const matrix<_T>& m1, double num);

    template <typename _T>
    friend matrix<_T> operator *(const matrix<_T>& m1, double num);

    template<typename _T>
    friend std::ostream& operator <<(std::ostream& os, const matrix<_T>& mat);

    void set_elem(unsigned int i, unsigned int j,const T& elem);
    T& get_elem(unsigned int i, unsigned int j);
    T& operator ()(unsigned int i, unsigned int j);
    bool isSquare();
    unsigned int getCountRows() const;
    unsigned int getCountCols() const;

    Iterator<T> iteratorBegin();
    Iterator<T> iteratorEnd();
};

#include "matrix_impl.h"
#endif // MATRIX_H
