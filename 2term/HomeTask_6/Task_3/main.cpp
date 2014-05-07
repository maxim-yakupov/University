#include <iostream>
#include "sharedpointer.h"
#include "testSharedPointer.h"

using namespace std;

int main()
{
    //test
    TestSharedPointer testSharedPointer;
    QTest::qExec(&testSharedPointer);
    //end test

    cout << "Inits empty SharedPointer p1\n";
    SharedPointer<int> p1;
    cout << "p1 counter: " << p1.counter() << endl;
    {
        cout << "====Block begins\n";
        cout << "-SharedPointer p2 inits with p1\n";
        SharedPointer<int> p2 (p1);
        cout << "p1 counter: " << p1.counter() << endl;
        cout << "p2 counter: " << p2.counter() << endl;
        cout << "-SharedPointer p3 inits with p1\n";
        SharedPointer<int> p3 (p2);
        cout << "p1 counter: " << p1.counter() << endl;
        cout << "p2 counter: " << p2.counter() << endl;
        cout << "p3 counter: " << p3.counter() << endl;
        cout << "====Block ends\n";
    }
    cout << "-SharedPointer p4 inits with 42\n";
    SharedPointer<int> p4 (new int(42));
    cout << "p4 = " << *p4 << endl;

    cout << "p1 counter: " << p1.counter() << endl;
    cout << "p4 counter: " << p4.counter() << endl;

    cout << "\np1 is nullptr: " << (p1.isNullPtr()? "true" : "false") << endl;
    cout << "p4 is nullptr: " << (p4.isNullPtr()? "true" : "false") << endl;

    cout << "\nMake p4=p1\n";
    p4 = p1;
    cout << "p4 is nullptr: " << (p4.isNullPtr()? "true" : "false") << endl;

    return 0;
}

