#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "set.h"

class TestSet : public QObject
{
    Q_OBJECT
public:
    explicit TestSet(QObject *parent = 0) : QObject(parent) {}
private:
    Set<int>* s1;
    Set<int>* s2;
private slots:
    void init()
    {
        s1 = new Set<int>;
        s2 = new Set<int>;
    }
    void testSetContains()
    {
        s1->add(1);
        QCOMPARE(s1->contains(1), true);
    }
    void testEmptySetAdd()
    {
        s1->add(1);
        s2->add(2);
        QCOMPARE(s1->contains(1), true);
        QCOMPARE(s2->contains(1), false);
        QCOMPARE(s1->contains(2), false);
        QCOMPARE(s2->contains(2), true);
    }
    void testSetAdd()
    {
        s1->add(1);
        s1->add(2);
        s2->add(1);
        s2->add(2);
        QCOMPARE(s1->contains(1), true);
        QCOMPARE(s2->contains(1), true);
        QCOMPARE(s1->contains(2), true);
        QCOMPARE(s2->contains(2), true);
    }
    void testEmptySetRemove()
    {
        s1->remove(1);
        s2->remove(2);
        QCOMPARE(s1->contains(1), false);
        QCOMPARE(s2->contains(1), false);
        QCOMPARE(s1->contains(2), false);
        QCOMPARE(s2->contains(2), false);
    }
    void testSetRemove()
    {
        s1->add(1);
        s1->add(2);
        s2->add(1);
        s2->add(2);
        QCOMPARE(s1->contains(1), true);
        QCOMPARE(s2->contains(1), true);
        QCOMPARE(s1->contains(2), true);
        QCOMPARE(s2->contains(2), true);
        s1->remove(1);
        s2->remove(2);
        QCOMPARE(s1->contains(1), false);
        QCOMPARE(s2->contains(2), false);
    }
    void testSetIntersectionSet()
    {
        s1->add(1);
        s1->add(2);
        s1->add(5);
        s1->add(7);
        s2->add(1);
        s2->add(3);
        s2->add(4);
        s2->add(5);
        Set<int> s3 = s1->intersectionSet(*s2);
        QCOMPARE(s3.contains(1), true);
        QCOMPARE(s3.contains(2), false);
        QCOMPARE(s3.contains(3), false);
        QCOMPARE(s3.contains(4), false);
        QCOMPARE(s3.contains(5), true);
        QCOMPARE(s3.contains(6), false);
        QCOMPARE(s3.contains(7), false);
    }
    void testSetUnionSet()
    {
        s1->add(1);
        s1->add(2);
        s1->add(5);
        s1->add(7);
        s2->add(1);
        s2->add(3);
        s2->add(4);
        s2->add(5);
        Set<int> s3 = s1->unionSet(*s2);
        QCOMPARE(s3.contains(1), true);
        QCOMPARE(s3.contains(2), true);
        QCOMPARE(s3.contains(3), true);
        QCOMPARE(s3.contains(4), true);
        QCOMPARE(s3.contains(5), true);
        QCOMPARE(s3.contains(6), false);
        QCOMPARE(s3.contains(7), true);
    }
    void cleanup()
    {
        delete s1;
        delete s2;
    }
};

