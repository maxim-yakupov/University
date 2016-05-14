#include <iostream>
#include <QDebug>
#include "vector.h"
#include "testVector.h"

using namespace std;

int main()
{
    //test
    TestVector testVector;
    QTest::qExec(&testVector);
    //end test

    Vector<int, 5, 0> v1;
    Vector<int, 5, 0> v2(1, 2, 3, 4, 5, 6);
    Vector<int, 5, 0> v3(1, -3, 3, 4, -4);
    qDebug() << "v1 is null-vector" << (v1.isNullVector() ? "+" : "-");
    qDebug() << "v2 is null-vector" << (v2.isNullVector() ? "+" : "-");
    qDebug() << "v3 is null-vector" << (v3.isNullVector() ? "+" : "-");
    qDebug() << "v1: " << v1.toQString();
    qDebug() << "v2: " << v2.toQString();
    qDebug() << "v3: " << v3.toQString();

    qDebug() << "v2 + v3: " << (v2 + v3).toQString();
    qDebug() << "v2 * v3: " << v2 * v3;
    qDebug() << "v1 + v3: " << (v1 + v3).toQString();
    qDebug() << "v1 * v3: " << v1 * v3;

    Vector<int, 5, 0> v4(v3);
    qDebug() << "v4 is null-vector" << (v4.isNullVector() ? "+" : "-");
    qDebug() << "v4: " << v4.toQString();
    qDebug() << "v4 + v3: " << (v4 + v3).toQString();
    qDebug() << "v4 * v3: " << v4 * v3;
    return 0;
}
