#include <iostream>
#include "set.h"
#include "testSet.h"

using namespace std;

int main()
{
    //test
    TestSet testSet;
    QTest::qExec(&testSet);
    //end test

    Set<int> s;
    s.add(1);
    s.add(2);
    s.add(5);
    s.add(7);
    Set<int> d;
    d.add(1);
    d.add(3);
    d.add(4);
    d.add(5);
    Set<int> i = s.intersectionSet(d);
    Set<int> u = s.unionSet(d);
    cout << "  s d i u" << endl;
    for (int p = 1; p < 8; p++)
    {
        cout << p;
        cout << " " << (s.contains(p) ? "+" : "-");
        cout << " " << (d.contains(p) ? "+" : "-");
        cout << " " << (i.contains(p) ? "+" : "-");
        cout << " " << (u.contains(p) ? "+" : "-") << endl;
    }
    return 0;
}

