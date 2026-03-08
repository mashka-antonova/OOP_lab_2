#include "test.h"

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <utility>
#include "matrix.h"

void MatrixTests::runTest(const std::string &testName, void (MatrixTests::*testFuction)()) {
    try {
        (this->*testFuction)();
        ++passedCount;
        std::cout << "[OK] " << testName << std::endl;
    }
    catch (const std::exception& exception) {
        ++failedCount;
        std::cout << "[FAIL] " << testName << ": " << exception.what() << std::endl;
    }
}

void MatrixTests::requireCondition(bool condition, const std::string &message) {
    if (!condition)
        throw std::runtime_error(message);
}

//getCountRows/getCountCols/isSquare
void MatrixTests::testConstructorGetters() {
    Matrix<int> matrixValue(2, 3);
    requireCondition(matrixValue.getCountRows() == 2, "rows mismatch");
    requireCondition(matrixValue.getCountCols() == 3, "columns mismatch");
    requireCondition(!matrixValue.isSquare(), "matrix should not be square");
}

//getElem/setElem/()
void MatrixTests::testSetGetOperator()
{
    Matrix<int> matrixValue(2, 2);
    matrixValue.setElem(0, 0, 7);
    matrixValue(1, 1) = 9;
    requireCondition(matrixValue.getElem(0, 0) == 7, "wrong value in [0,0]");
    requireCondition(matrixValue.getElem(1, 1) == 9, "wrong value in [1,1]");
}

//конструктор копирования и оператор присваивания
void MatrixTests::testCopyConstructorAndAssignment()
{
    Matrix<int> matrixA{{1, 2}, {3, 4}};
    Matrix<int> matrixB(matrixA);
    Matrix<int> matrixC(2, 2);
    matrixC = matrixA;
    requireCondition(matrixB.getElem(0, 1) == 2, "copy constructor failed");
    requireCondition(matrixC.getElem(1, 0) == 3, "copy assignment failed");
}

//конструктор перемещения
void MatrixTests::testMoveConstructor()
{
    Matrix<int> sourceMatrix{{5, 6}, {7, 8}};
    Matrix<int> movedMatrix(std::move(sourceMatrix));
    requireCondition(movedMatrix.getElem(0, 0) == 5, "move constructor failed");
}

//+/+=
void MatrixTests::testMatrixPlusAndPlusEq()
{
    Matrix<int> matrixA{{1, 2}, {3, 4}};
    Matrix<int> matrixB{{4, 3}, {2, 1}};
    Matrix<int> matrixC = matrixA + matrixB;
    matrixA += matrixB;
    requireCondition(matrixC.getElem(1, 1) == 5, "+ failed");
    requireCondition(matrixA.getElem(0, 1) == 5, "+= failed");
}

//-/-=
void MatrixTests::testMatrixMinusAndMinusEq()
{
    Matrix<int> matrixA{{8, 7}, {6, 5}};
    Matrix<int> matrixB{{1, 2}, {3, 4}};
    Matrix<int> matrixC = matrixA - matrixB;
    matrixA -= matrixB;
    requireCondition(matrixC.getElem(1, 0) == 3, "- failed");
    requireCondition(matrixA.getElem(0, 0) == 7, "-= failed");
}

//*
void MatrixTests::testMatrixMultiplication()
{
    Matrix<int> matrixA{{1, 2, 3}, {4, 5, 6}};
    Matrix<int> matrixB{{7, 8}, {9, 10}, {11, 12}};
    Matrix<int> matrixC = matrixA * matrixB;
    requireCondition(matrixC.getCountRows() == 2 && matrixC.getCountRows() == 2, "wrong multiplication shape");
    requireCondition(matrixC.getElem(0, 0) == 58, "wrong multiplication value");
}

//операторы: матрица + число
void MatrixTests::testMatrixNumberOperators()
{
    Matrix<int> matrixValue{{2, 4}, {6, 8}};
    auto plusResult = matrixValue + 2.0;
    auto minusResult = matrixValue - 1.0;
    auto multiplyResult = matrixValue * 3.0;
    auto divideResult = matrixValue / 2.0;
    requireCondition(plusResult.getElem(0, 0) == 4, "plus number failed");
    requireCondition(minusResult.getElem(1, 1) == 7, "minus number failed");
    requireCondition(multiplyResult.getElem(0, 1) == 12, "multiply number failed");
    requireCondition(divideResult.getElem(1, 0) == 3, "divide number failed");
}

//итератор
void MatrixTests::testIteratorMethods()
{
    Matrix<int> matrixValue{{1, 2}, {3, 4}};
    auto iterator = matrixValue.iteratorBegin();
    auto iteratorEnd = matrixValue.iteratorEnd();
    int sum = 0;
    while (iterator != iteratorEnd)
    {
        sum += *iterator;
        ++iterator;
    }
    requireCondition(sum == 10, "iterator failed");
}

//<<
void MatrixTests::testOutputOperator()
{
    Matrix<int> matrixValue{{1, 2}, {3, 4}};
    std::ostringstream outputStream;
    outputStream << matrixValue;
    requireCondition(!outputStream.str().empty(), "stream output is empty");
}

//проверка исключений
void MatrixTests::testExceptions()
{
    Matrix<int> matrixValue(1, 1);
    bool caughtIndex = false;
    bool caughtDivision = false;
    bool caughtIterator = false;

    try
    {
        matrixValue.getElem(3, 0);
    }
    catch (const MatrixBaseException &)
    {
        caughtIndex = true;
    }

    try
    {
        auto result = matrixValue / 0.0;
        (void) result;
    }
    catch (const MatrixBaseException &)
    {
        caughtDivision = true;
    }

    auto iterator = matrixValue.iteratorEnd();
    try
    {
        (void) iterator.value();
    }
    catch (const IteratorException &)
    {
        caughtIterator = true;
    }

    requireCondition(caughtIndex && caughtDivision && caughtIterator,
                     "expected exceptions were not thrown");
}

int MatrixTests::runAll()
{
    runTest("constructor/getters", &MatrixTests::testConstructorGetters);
    runTest("set/get/operator()", &MatrixTests::testSetGetOperator);
    runTest("copy constructor and assignment", &MatrixTests::testCopyConstructorAndAssignment);
    runTest("move constructor", &MatrixTests::testMoveConstructor);
    runTest("matrix + and +=", &MatrixTests::testMatrixPlusAndPlusEq);
    runTest("matrix - and -=", &MatrixTests::testMatrixMinusAndMinusEq);
    runTest("matrix * matrix", &MatrixTests::testMatrixMultiplication);
    runTest("matrix with number operators", &MatrixTests::testMatrixNumberOperators);
    runTest("iterator methods", &MatrixTests::testIteratorMethods);
    runTest("operator<<", &MatrixTests::testOutputOperator);
    runTest("exceptions", &MatrixTests::testExceptions);

    std::cout << "Passed: " << passedCount << ", Failed: " << failedCount << std::endl;
    return failedCount == 0 ? 0 : 1;
}
