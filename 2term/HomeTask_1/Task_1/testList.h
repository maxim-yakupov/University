#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "doublylinkedlist.h"
#include "singlylinkedlist.h"

class TestList : public QObject
{
    Q_OBJECT
public:
    explicit TestList(QObject *parent = 0) : QObject(parent) {}
private:
    DoublyLinkedList *dLList;
    SinglyLinkedList *sLList;
private slots:
    void initTestCase()
    {
        dLList = new DoublyLinkedList;
        sLList = new SinglyLinkedList;
    }
    void testEmptyDLListLength()
    {
        QCOMPARE(static_cast<int>(dLList->length()), 0);
    }
    void testEmptySLListLength()
    {
        QCOMPARE(static_cast<int>(sLList->length()), 0);
    }
    void testEmptyDLListDeletePos()
    {
        dLList->deletePos(1);
        QCOMPARE(static_cast<int>(dLList->length()), 0);
    }
    void testEmptySLListDeletePos()
    {
        sLList->deletePos(1);
        QCOMPARE(static_cast<int>(sLList->length()), 0);
    }
    void testDLListAddValue()
    {
        dLList->addValue(2);
        QCOMPARE(static_cast<int>(dLList->length()), 1);
        dLList->deletePos(1);
    }
    void testSLListAddValue()
    {
        sLList->addValue(2);
        QCOMPARE(static_cast<int>(sLList->length()), 1);
        sLList->deletePos(1);
    }
    void testDLListAddPos()
    {
        dLList->addPos(5, 4);
        QCOMPARE(static_cast<int>(dLList->length()), 1);
        dLList->deletePos(1);
    }
    void testSLListAddPos()
    {
        sLList->addPos(5, 4);
        QCOMPARE(static_cast<int>(sLList->length()), 1);
        sLList->deletePos(1);
    }
    void testDLListDeletePos()
    {
        dLList->addPos(5, 4);
        dLList->deletePos(1);
        QCOMPARE(static_cast<int>(dLList->length()), 0);
    }
    void testSLListDeletePos()
    {
        sLList->addPos(5, 4);
        sLList->deletePos(1);
        QCOMPARE(static_cast<int>(sLList->length()), 0);
    }
    void cleanupTestCase()
    {
        delete dLList;
        delete sLList;
    }
};
