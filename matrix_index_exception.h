#ifndef MATRIX_INDEX_EXCEPTION_H
#define MATRIX_INDEX_EXCEPTION_H

#include "matrix_base_exception.h"

class MatrixIndexException : public MatrixBaseException
{
public:
    explicit MatrixIndexException(const std::string &msg);
};


#endif // MATRIX_INDEX_EXCEPTION_H
