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

template<typename T>
Iterator<T>::Iterator(Matrix<T>& containerObj, unsigned int startIndex)
    : container(&containerObj), index(startIndex) {}

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (isEnd())
        throw IteratorException("Iterator is already at end");
    ++index;
    return *this;
}

template<typename T>
T Iterator<T>::value() {
    if (isEnd())
        throw IteratorException("Can't read value at end");
    return container->data[index];
}

template<typename T>
bool Iterator<T>::isEnd() {
    return index >= container->rows * container->cols;
}

template<typename T>
Iterator<T>& Iterator<T>::operator++()
{
    this->next();
    return *this;
}

template<typename T>
T& Iterator<T>::operator *() {
    if (isEnd())
        throw IteratorException("Can't get value at end");
    return container->data[index];
}

template<typename T>
bool Iterator<T>::operator==(Iterator<T> &b) {
    return container == b.container && index == b.index;
}

template<typename T>
bool Iterator<T>::operator!=(Iterator<T> &b) {
    return !(*this == b);
}

#endif
