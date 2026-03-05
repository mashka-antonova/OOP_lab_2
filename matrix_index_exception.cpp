#include "matrix_index_exception.h"

MatrixIndexException::MatrixIndexException(const std::string &msg)
    : MatrixBaseException("Matrix Index Error: " + msg) {}
