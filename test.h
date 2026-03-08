#ifndef MATRIX_TESTS_H
#define MATRIX_TESTS_H

#include <functional>
#include <string>

class MatrixTests
{
public:
    int runAll();

private:

    int passedCount = 0;
    int failedCount = 0;

    void runTest(const std::string &testName, void (MatrixTests::*testFuction)());
    static void requireCondition(bool condition, const std::string &message);

    void testConstructorGetters();
    void testSetGetOperator();
    void testCopyConstructorAndAssignment();
    void testMoveConstructor();
    void testMatrixPlusAndPlusEq();
    void testMatrixMinusAndMinusEq();
    void testMatrixMultiplication();
    void testMatrixNumberOperators();
    void testIteratorMethods();
    void testOutputOperator();
    void testExceptions();
};

#endif // MATRIX_TESTS_H
