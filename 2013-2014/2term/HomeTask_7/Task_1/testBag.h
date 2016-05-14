#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "bag.h"

class TestBag : public QObject
{
    Q_OBJECT
public:
    explicit TestBag(QObject *parent = 0) : QObject(parent) {}
private:
    Bag<int>* s1;
    Bag<int>* s2;
private slots:
    void init()
    {
        s1 = new Bag<int>;
        s2 = new Bag<int>;
    }
    void testBagContains()
    {
        s1->add(1);
        QCOMPARE(s1->contains(1), true);
    }
    void testEmptyBagAdd()
    {
        s1->add(1);
        s2->add(2);
        QCOMPARE(s1->contains(1), true);
        QCOMPARE(s2->contains(1), false);
        QCOMPARE(s1->contains(2), false);
        QCOMPARE(s2->contains(2), true);
    }
    void testBagAdd()
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
    void testEmptyBagRemove()
    {
        s1->remove(1);
        s2->remove(2);
        QCOMPARE(s1->contains(1), false);
        QCOMPARE(s2->contains(1), false);
        QCOMPARE(s1->contains(2), false);
        QCOMPARE(s2->contains(2), false);
    }
    void testBagRemove()
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
    void testBagIntersectionBag()
    {
        s1->add(1);
        s1->add(2);
        s1->add(5);
        s1->add(7);
        s2->add(1);
        s2->add(3);
        s2->add(4);
        s2->add(5);
        Bag<int> s3 = s1->intersectionBag(*s2);
        QCOMPARE(s3.contains(1), true);
        QCOMPARE(s3.contains(2), false);
        QCOMPARE(s3.contains(3), false);
        QCOMPARE(s3.contains(4), false);
        QCOMPARE(s3.contains(5), true);
        QCOMPARE(s3.contains(6), false);
        QCOMPARE(s3.contains(7), false);
    }
    void testBagUnionBag()
    {
        s1->add(1);
        s1->add(2);
        s1->add(5);
        s1->add(7);
        s2->add(1);
        s2->add(3);
        s2->add(4);
        s2->add(5);
        Bag<int> s3 = s1->unionBag(*s2);
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

