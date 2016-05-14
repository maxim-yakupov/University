#include <iostream>
#include "stdlib.h"
#include "sorter.h"
#include "testSorter.h"

using namespace std;

template<class T>
class Less : public Comparator<T>
{
public:
    bool compare(T a, T b)
    {
        return a < b;
    }
};

template<class T>
void write(T a[], int size)
{
    for(int i = 0; i < size; i++)
    {
        cout << a[i] << " ";
    }
    cout << endl;
}
int main()
{
    //test
    TestSorter testSorter;
    QTest::qExec(&testSorter);
    //end test

    srand(4);
    int a[5];
    for (int i = 0; i < 5; i++)
    {
        a[i] = rand() % 128;
    }
    cout << "input data:             ";
    write(a, 5);
    Less<int> comp;
    int* b = Sorter<int>::sort(a, 5, &comp);
    cout << "input data(after sort): ";
    write(a, 5);
    cout << "result data: ";
    write(b, 5);
    cout << "if input data befor & after sort are equal all is ok";
    delete [] b;
    return 0;
}

