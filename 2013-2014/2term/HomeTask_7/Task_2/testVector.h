#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "vector.h"

class TestVector : public QObject
{
    Q_OBJECT
public:
    explicit TestVector(QObject *parent = 0) : QObject(parent) {}
private slots:
    void testZeroVector()
    {
        Vector<int, 5, 0> v1;
        QCOMPARE(v1.isNullVector(), true);
        qDebug(v1.toQString().toUtf8().data());
    }
    void testVectorInitWithValuesAndScalarMultiplication()
    {
        Vector<int, 5, 0> v2(1, 2, 3, 4, 5, 6);
        QCOMPARE(v2.isNullVector(), false);
        qDebug(v2.toQString().toUtf8().data());
        QCOMPARE(v2 * v2, 1 + 4 + 9 + 16 + 25);
    }
    void testVectorInitWithVectorAndScalarMultiplication()
    {
        Vector<int, 5, 0> v2(1, 2, 3, 4, 5, 6);
        Vector<int, 5, 0> v3(v2);
        QCOMPARE(v3.isNullVector(), false);
        qDebug(v3.toQString().toUtf8().data());
        QCOMPARE(v3 * v2, 1 + 4 + 9 + 16 + 25);
    }
    void testZeroDimentionalVector()
    {
        Vector<int, 0, 0> v0;
        qDebug(v0.toQString().toUtf8().data());
        QCOMPARE(v0.isNullVector(), true);
    }
    void testVectorSumm()
    {
        Vector<int, 5, 0> v2(1, 2, 3, 4, 5, 6);
        Vector<int, 5, 0> v3(1, -3, 3, 4, -4);
        qDebug(v2.toQString().toUtf8().data());
        qDebug(v3.toQString().toUtf8().data());
        qDebug() << "v2 + v3: " << (v2 + v3).toQString();
        Vector<int, 5, 0> v5(2, -1, 6, 8, 1);
        QCOMPARE(v2 + v3, v5);
    }
};

