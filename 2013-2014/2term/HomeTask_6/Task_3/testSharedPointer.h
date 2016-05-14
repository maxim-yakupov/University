#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "sharedpointer.h"

class TestSharedPointer : public QObject
{
    Q_OBJECT
public:
    explicit TestSharedPointer(QObject *parent = 0) : QObject(parent) {}
private slots:
    void testSharedPointerInitWithAnotherSharedPointer()
    {
        SharedPointer<int> a;
        SharedPointer<int> b(a);
        QCOMPARE(static_cast<int>(a.counter()), 2);
        QCOMPARE(static_cast<int>(b.counter()), 2);
        QCOMPARE(a.operator ->(), b.operator ->());
    }
    void testSharedPointerIsNullptr()
    {
        SharedPointer<int> a;
        QCOMPARE(a.isNullPtr(), true);
    }
    void testSharedPointerOperatorEqual()
    {
        SharedPointer<int> a(new int(42));
        SharedPointer<int> b(nullptr);
        b = a;
        QCOMPARE(*a,*b);
        QCOMPARE(*a, 42);
        QCOMPARE(a.operator ->(), b.operator ->());
    }
};
