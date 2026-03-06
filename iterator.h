#ifndef ITERATOR_H
#define ITERATOR_H

#include "iterator_exception.h"

template<typename T>
class matrix;

template<typename T>
class Iterator
{
public:
    Iterator(matrix<T>& containerObj, unsigned int startIndex = 0);
    Iterator<T> next();
    T value();
    bool is_end();
    Iterator<T>& operator++();
    T& operator *();
    bool operator ==(Iterator<T> &b);
    bool operator !=(Iterator<T> &b);
private:
    matrix<T>* container;
    unsigned int index;
};

#endif // ITERATOR_H
