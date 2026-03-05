#include "matrix_base_exception.h"

#include "matrix_base_exception.h"

MatrixBaseException::MatrixBaseException(const std::string &msg) : message(msg) {}

const char *MatrixBaseException::what() const noexcept
{
    return message.c_str();
}
