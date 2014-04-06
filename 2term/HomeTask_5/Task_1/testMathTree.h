#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "mathtree.h"

class TestMathTree : public QObject
{
    Q_OBJECT
public:
    explicit TestMathTree(QObject *parent = 0) : QObject(parent) {}
private:
    MathTree* tree;
private slots:
    void init()
    {
        tree = new MathTree();
    }
    void testEmptyMTreeCompute()
    {
        QCOMPARE(static_cast<int>(tree->compute()), 0);
    }
    void testMTreeCompute()
    {
        char* tStr = new char[20];
        tStr = "(* (+ 1.2 3.3) 1.1)\0";
        tree->operator()(tStr);
        QCOMPARE(static_cast<double>(tree->compute()), 4.95);
        qDebug(tStr);
        tree->operator()("(+ 1.2 3)");
        QCOMPARE(static_cast<double>(tree->compute()), 4.2);
        delete [] tStr;
    }
    void cleanup()
    {
        delete tree;
    }
};

