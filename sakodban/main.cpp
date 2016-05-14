#include <QtWidgets>
#include "gamescene.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    //qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    GameScene scene;

    QGraphicsView view(&scene);
    //view.setFixedSize(view.frameRect().size() + QSize(20, 20));
    view.setMinimumSize(a.desktop()->availableGeometry().size() + QSize(-100, -30));
    view.setSceneRect(view.geometry());
    view.setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view.show();

    return a.exec();
}
