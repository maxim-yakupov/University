#include "bashimviewer.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    BashImViewer bimv;

    bimv.show();

    return a.exec();
}
