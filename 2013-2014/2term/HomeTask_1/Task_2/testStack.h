#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>
#include "arraystack.h"
#include "pointerstack.h"

class TestStack : public QObject
{
    Q_OBJECT
public:
    explicit TestStack(QObject *parent = 0) : QObject(parent) {}
private:
    ArrayStack<int> *testArrayStack;
    PointerStack<int> *testPointerStack;
private slots:
    void initTestCase()
    {
        testArrayStack = new ArrayStack<int>;
        testPointerStack = new PointerStack<int>;
    }
    void testEmptyArrayStack()
    {
        QCOMPARE(testArrayStack->isEmpty(), false);
    }
    void testEmptyPointerStack()
    {
        QCOMPARE(testPointerStack->isEmpty(), false);
    }
    void testEmptyArrayStackPop()
    {
        testArrayStack->pop();
        QCOMPARE(testArrayStack->isEmpty(), false);
    }
    void testEmptyPointerStackPop()
    {
        testPointerStack->pop();
        QCOMPARE(testPointerStack->isEmpty(), false);
    }
    void testArrayStackPush()
    {
        testArrayStack->push(6);
        QCOMPARE(testArrayStack->isEmpty(), true);
        QCOMPARE(testArrayStack->top(), 6);
    }
    void testPointerStackPush()
    {
        testPointerStack->push(6);
        QCOMPARE(testPointerStack->isEmpty(), true);
        QCOMPARE(testPointerStack->top(), 6);
    }
    void testArrayStackPop()
    {
        testArrayStack->push(6);
        QCOMPARE(testArrayStack->isEmpty(), true);
        QCOMPARE(testArrayStack->top(), 6);
        testArrayStack->push(7);
        QCOMPARE(testArrayStack->isEmpty(), true);
        QCOMPARE(testArrayStack->top(), 7);
        testArrayStack->pop();
        QCOMPARE(testArrayStack->isEmpty(), true);
        QCOMPARE(testArrayStack->top(), 6);
    }
    void testPointerStackPop()
    {
        testPointerStack->push(6);
        QCOMPARE(testPointerStack->isEmpty(), true);
        QCOMPARE(testPointerStack->top(), 6);
        testPointerStack->push(7);
        QCOMPARE(testPointerStack->isEmpty(), true);
        QCOMPARE(testPointerStack->top(), 7);
        testPointerStack->pop();
        QCOMPARE(testPointerStack->isEmpty(), true);
        QCOMPARE(testPointerStack->top(), 6);
    }
    void cleanupTestCase()
    {
        delete testArrayStack;
        delete testPointerStack;
    }
};

