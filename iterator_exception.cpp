#include "iterator_exception.h"

#include "iterator_exception.h"

IteratorException::IteratorException(const std::string &msg)
    : MatrixBaseException("Iterator Error: " + msg) {}
