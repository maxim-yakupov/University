#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "uniquelist.h"

class TestUniqueList : public QObject
{
    Q_OBJECT
public:
    explicit TestUniqueList(QObject *parent = 0) : QObject(parent) {}
private:
    UniqueList *list;
private slots:
    void init()
    {
        list = new UniqueList;
    }
    void testEmptyUniqueListDeleteValue()
    {
        try
        {
            list->deleteValue(1);
            QFAIL("Expected exception");
        }
        catch(...)
        {
            qDebug("Exception catched");
        }
        QCOMPARE(static_cast<int>(list->length()), 0);
    }
    void testUniqueListDeleteValue()
    {
        try
        {
            list->addValue(2);
        }
        catch(...)
        {
            QFAIL("Exception unexpectedly catched");
        }
        QCOMPARE(static_cast<int>(list->length()), 1);
        try
        {
            list->deleteValue(2);
        }
        catch(...)
        {
            qDebug("Exception unexpectedly catched");
        }
        QCOMPARE(static_cast<int>(list->length()), 0);
    }
    void testUniqueListAddValue()
    {
        try
        {
            list->addValue(2);
        }
        catch(...)
        {
            QFAIL("Exception unexpectedly catched");
        }
        QCOMPARE(static_cast<int>(list->length()), 1);
        list->deletePos(1);
        QCOMPARE(static_cast<int>(list->length()), 0);
    }
    void testUniqueListAddPos()
    {
        try
        {
            list->addPos(5, 4);
        }
        catch(...)
        {
            QFAIL("Exception unexpectedly catched");
        }
        QCOMPARE(static_cast<int>(list->length()), 1);
        list->deletePos(1);
        QCOMPARE(static_cast<int>(list->length()), 0);
    }
    void testUniqueListAddValueEqualValues()
    {
        try
        {
            list->addValue(4);
        }
        catch(...)
        {
            QFAIL("Exception unexpectedly catched");
        }
        try
        {
            list->addValue(4);
            QFAIL("Expected exception");
        }
        catch(...)
        {
            qDebug("Exception catched");
        }
        QCOMPARE(static_cast<int>(list->length()), 1);
        list->deletePos(1);
        QCOMPARE(static_cast<int>(list->length()), 0);
    }
    void testUniqueListAddPosEqualValues()
    {
        try
        {
            list->addPos(5, 4);
        }
        catch(...)
        {
            QFAIL("Exception unexpectedly catched");
        }
        try
        {
            list->addPos(3, 4);
            QFAIL("Expected exception");
        }
        catch(...)
        {
            qDebug("Exception catched");
        }
        QCOMPARE(static_cast<int>(list->length()), 1);
        list->deletePos(1);
        QCOMPARE(static_cast<int>(list->length()), 0);
    }
    void cleanup()
    {
        delete list;
    }
};
