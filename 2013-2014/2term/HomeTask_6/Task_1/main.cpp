#include <iostream>

using namespace std;

class A
{
public:
    A()
    {
        cout << "created A\n";
    }
    ~A()
    {
        cout << "destroyed A\n";
    }
};

class B
{
public:
    B()
    {
        cout << "created B\n";
    }
    ~B()
    {
        cout << "destroyed B\n";
    }
};

class C
{
public:
    C()
    {
        cout << "created C\n";
    }
    ~C()
    {
        cout << "destroyed C\n";
    }
};

class ExceptionalClass
{
};

int main()
{
    try
    {
        A a;
        B b;
        C c;
        throw ExceptionalClass();
    }
    catch(ExceptionalClass &)
    {
        cout << "exception catched\n";
    }
    return 0;
}

