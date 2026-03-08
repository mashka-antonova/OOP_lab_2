#ifndef ITERATOR_H
#define ITERATOR_H

#include "iterator_exception.h"

template<typename T>
class Matrix;

template<typename T>
class Iterator
{
public:
    Iterator(Matrix<T>& containerObj, unsigned int startIndex = 0);
    Iterator<T> next();
    T value();
    bool isEnd();
    Iterator<T>& operator++();
    T& operator *();
    bool operator ==(Iterator<T> &b);
    bool operator !=(Iterator<T> &b);
private:
    Matrix<T>* container;
    unsigned int index;
};

#endif // ITERATOR_H
