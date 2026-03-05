#ifndef ITERATOR_EXCEPTION_H
#define ITERATOR_EXCEPTION_H

#include "matrix_base_exception.h"

class IteratorException : public MatrixBaseException
{
public:
    explicit IteratorException(const std::string &msg);
};


#endif // ITERATOR_EXCEPTION_H
