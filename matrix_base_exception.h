#ifndef MATRIX_BASE_EXCEPTION_H
#define MATRIX_BASE_EXCEPTION_H

#include <exception>
#include <string>

class MatrixBaseException : public std::exception
{
protected:
    std::string message;

public:
    explicit MatrixBaseException(const std::string &msg);
    const char* what() const noexcept override;
};

#endif // MATRIX_BASE_EXCEPTION_H
