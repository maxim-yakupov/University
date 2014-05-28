#include <QtWidgets>
#include "gamescene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    GameScene scene;

    QGraphicsView view(&scene);
    view.show();

    QTimer timer;
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(advance()));
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(processCollisions()));
    QObject::connect(&timer, SIGNAL(timeout()), &scene, SLOT(otherCannonsShot()));
    timer.start(1000 / 33);

    return a.exec();
}
