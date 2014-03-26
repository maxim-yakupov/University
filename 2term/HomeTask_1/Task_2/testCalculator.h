#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>
#include "calculator.h"

class TestCalculator : public QObject
{
    Q_OBJECT
public:
    explicit TestCalculator(QObject *parent = 0) : QObject(parent) {}
private:
    Calculator<ArrayStack<TokenStruct>, PointerStack<double>> *test;
    char* testStr;
private slots:
    void initTestCase()
    {
        test = new Calculator<ArrayStack<TokenStruct>, PointerStack<double>>;
    }
    void testComputeOfEmptyExpression()
    {
        QCOMPARE(test->compute(), 0.0);
    }
    void init()
    {
        testStr = new char[8];
        testStr = "4+5.0\0";
    }
    void testCompute()
    {
        test->operator ()(testStr);
        QCOMPARE(test->compute(), 9.0);
    }
    void cleanup()
    {
        delete [] testStr;
    }
    void cleanupTestCase()
    {
        delete test;
    }
};
