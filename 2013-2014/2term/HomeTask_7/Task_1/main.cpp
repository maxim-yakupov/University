#include <iostream>
#include "bag.h"
#include "testBag.h"

using namespace std;

int main()
{
    //test
    TestBag testBag;
    QTest::qExec(&testBag);
    //end test

    Bag<int> s;
    s.add(1);
    s.add(2);
    s.add(5);
    s.add(7);
    Bag<int> d;
    d.add(1);
    d.add(3);
    d.add(4);
    d.add(5);
    Bag<int> i = s.intersectionBag(d);
    Bag<int> u = s.unionBag(d);
    cout << "  s d i u" << endl;
    for (int p = 1; p < 8; p++)
    {
        cout << p;
        cout << " " << s.quantity(p);
        cout << " " << d.quantity(p);
        cout << " " << i.quantity(p);
        cout << " " << u.quantity(p) << endl;
    }
    return 0;
}

