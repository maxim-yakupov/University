#pragma once

#include <QGraphicsScene>
#include "cannon.h"
#include "bullet.h"

class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene(unsigned int enemies = 0);
    ~GameScene();
public slots:
    void processCollisions();
    void otherCannonsShot();
protected:
    void keyPressEvent(QKeyEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent * mouseEvent);
private:
    Cannon* cannon;
    QGraphicsTextItem* statsItem;
    QList<Bullet*> bullets;
    QList<Cannon*> cannons;
    unsigned int numberOfEnemies;

    void help();
    void startGame(int dNumber);
    void genLandscape();
    void phisics(Cannon* can);
    bool isOnSurface(Cannon* can);
    void placeCannons(unsigned int number);
    bool placeCannon(qreal x, qreal y, qreal dir);
    Bullet* makeShot(Cannon *cannon);
    void stats();
    void showWinner(bool winner);
};
