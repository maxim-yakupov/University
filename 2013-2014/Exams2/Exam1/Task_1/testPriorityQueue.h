#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "priorityqueue.h"

class TestPriorityQueue : public QObject
{
    Q_OBJECT
public:
    explicit TestPriorityQueue(QObject *parent = 0) : QObject(parent) {}
private:
    PriorityQueue<int> *queue;
private slots:
    void initTestCase()
    {
        queue = new PriorityQueue<int>();
    }
    void testEmptyQueueDequeue()
    {
        try {
            queue->dequeue();
        } catch (PriorityQueue<int>::EmptyQueueReturnException &)
        {
            qDebug("Queue is empty! OK");
        }
    }
    void testEmptyQueueEnqueue()
    {
        queue->enqueue(1, 1);
        QCOMPARE(queue->dequeue(), 1);
    }
    void testDequeue()
    {
        queue->enqueue(1, 9);
        queue->enqueue(3, 7);
        queue->enqueue(2, 8);
        QCOMPARE(queue->dequeue(), 1);
        QCOMPARE(queue->dequeue(), 2);
        QCOMPARE(queue->dequeue(), 3);
    }
    void cleanupTestCase()
    {
        delete queue;
    }
};
