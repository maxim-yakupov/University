#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "sorter.h"

class TestSorter : public QObject
{
    Q_OBJECT
public:
    explicit TestSorter(QObject *parent = 0) : QObject(parent) {}
    template<class T>
    class Less : public Comparator<T>
    {
    public:
        bool compare(T a, T b)
        {
            return a < b;
        }
    };

    template<class T>
    class More : public Comparator<T>
    {
    public:
        bool compare(T a, T b)
        {
            return a > b;
        }
    };

    template<class T>
    class LessOrEq : public Comparator<T>
    {
    public:
        bool compare(T a, T b)
        {
            return a <= b;
        }
    };
private slots:
    void testSorterWithLessComporator()
    {
        qsrand(4);
        int a[5];
        a[0] = 8;
        a[1] = 3;
        a[2] = 10;
        a[3] = 2;
        a[4] = 9;

        Less<int> comp;
        int* b = Sorter<int>::sort(a, 5, &comp);
        QCOMPARE(b[4], 2);
        QCOMPARE(b[3], 3);
        QCOMPARE(b[2], 8);
        QCOMPARE(b[1], 9);
        QCOMPARE(b[0], 10);
    }
    void testSorterWithMoreComporator()
    {
        qsrand(4);
        int a[5];
        a[0] = 8;
        a[1] = 3;
        a[2] = 10;
        a[3] = 2;
        a[4] = 9;

        More<int> comp;
        int* b = Sorter<int>::sort(a, 5, &comp);
        QCOMPARE(b[0], 2);
        QCOMPARE(b[1], 3);
        QCOMPARE(b[2], 8);
        QCOMPARE(b[3], 9);
        QCOMPARE(b[4], 10);
    }
    void testDoubleSorterWithLessComporator()
    {
        qsrand(4);
        double a[5];
        a[0] = 8;
        a[1] = 3;
        a[2] = 10;
        a[3] = 2;
        a[4] = 9;

        Less<double> comp;
        double* b = Sorter<double>::sort(a, 5, &comp);
        QCOMPARE(b[4], 2.0);
        QCOMPARE(b[3], 3.0);
        QCOMPARE(b[2], 8.0);
        QCOMPARE(b[1], 9.0);
        QCOMPARE(b[0], 10.0);
    }
};
