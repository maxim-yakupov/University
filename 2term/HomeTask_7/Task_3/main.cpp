#include "crossesandzeros.h"
#include <QApplication>
#include "testCrossesAndZerosLogic.h"

int main(int argc, char *argv[])
{
    //test
    TestCrossesAndZerosLogic testCrossesAndZerosLogic;
    QTest::qExec(&testCrossesAndZerosLogic);
    //end test

    QApplication a(argc, argv);
    CrossesAndZeros w;
    w.show();

    return a.exec();
}
