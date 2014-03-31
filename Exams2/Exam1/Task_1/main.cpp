#include <iostream>

#include "priorityqueue.h"
#include "testPriorityQueue.h"

using namespace std;

int main()
{
    //test
    TestPriorityQueue testQueue;
    QTest::qExec(&testQueue);
    //end test
    PriorityQueue<int> queue;
    queue.enqueue(1, 1);
    queue.enqueue(3, 3);
    queue.enqueue(2, 2);
    queue.enqueue(-1, -1);
    queue.enqueue(0, 0);
    while (true)
    {
        try {
            cout << queue.dequeue() << endl;
        } catch (PriorityQueue<int>::EmptyQueueReturnException &)
        {
            qDebug("Queue is empty!");
            break;
        }
    }
    return 0;
}

