#ifndef ITERATOR_IMPL_H
#define ITERATOR_IMPL_H

#include <iterator.h>

template<typename T>
Iterator<T>::Iterator(matrix<T>& containerObj, unsigned int startIndex)
    : container(containerObj), index(startIndex) {}

template<typename T>
Iterator<T> Iterator<T>::next() {
    if (is_end())
        throw IteratorException("Iterator is already at end");
    ++index;
    return *this;
}

template<typename T>
T Iterator<T>::value() {
    if (is_end())
        throw IteratorException("Can't read value at end");
    return container->data[index];
}

template<typename T>
bool Iterator<T>::is_end() {
    return index >= container->rows * container->columns;
}

template<typename T>
Iterator<T>& Iterator<T>::operator++()
{
    this->next();
    return *this;
}

template<typename T>
T& Iterator<T>::operator *() {
    if (is_end())
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

#endif // ITERATOR_IMPL_H
