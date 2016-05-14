#include "gamescene.h"
#include <QKeyEvent>
#include <QGraphicsSceneMouseEvent>
#include <QDebug>//
#include <QMessageBox>
#include <qmath.h>//

GameScene::GameScene(unsigned int enemies) : cannon(nullptr),
    statsItem(nullptr),
    numberOfEnemies(enemies)
{
    startGame(1);
    setBackgroundBrush(QBrush(QColor(0,0,255)));
    help();
}

GameScene::~GameScene()
{
    delete cannon;
    delete statsItem;
}

void GameScene::genLandscape()
{
    float ground[3][4] = {{0, 0, 25, 490}, {0, 0, 650, 25}, {650, 0, -25, 490}};
    QBrush brush(QColor(33, 33, 66));
    QPen pen(Qt::NoPen);
    for (int i = 0; i < 3; i++)
    {
        QGraphicsItem * item =
        addRect(QRectF(0, 0, ground[i][2], ground[i][3]), pen, brush);
        item->setData(0, "wall");
        item->setPos(QPointF(ground[i][0], ground[i][1]));
    }
    brush.setColor(QColor(33, 128, 33));
    addRect(QRectF(0, 465, 650, 25), pen, brush)->setData(0, "ground");
    float mountains[3][6] = {{100, 465, 185, 465, 150, 400}
                            ,{190, 465, 240, 465, 220, 400}
                            ,{250, 465, 345, 465, 292, 400}};
    brush.setColor(QColor(128, 128, 33));
    for (int i = 0; i < 3; i++)
    {
        QPolygonF polygon;
        polygon << QPointF(mountains[i][0] + 50 * i, mountains[i][1])
                << QPointF(mountains[i][2] + 50 * i, mountains[i][3])
                << QPointF(mountains[i][4] + 50 * i, mountains[i][5]);
        QGraphicsItem * item =
        addPolygon(polygon, pen, brush);
        item->setData(0, "mountain");
    }
    //rand mountains generation
    for (int i = 0; i < 3; i++)
    {
        int x1 = 50 + qrand() % 500;
        int x2 = x1 + 50 + qrand() % (575 - x1);
        QPolygonF polygon;
        polygon << QPointF(x1, 465)
                << QPointF(x2, 465)
                << QPointF(x1 + qrand() % 70, 100 + qrand() % 165);
        QGraphicsItem * item =
        addPolygon(polygon, pen, brush);
        item->setData(0, "mountain");
    }
    //
}

void GameScene::placeCannons(unsigned int number)
{
    for (unsigned int i = 0; i < number; i++)
    {
        while(!placeCannon(150 + qrand() % 450, qrand() % 490, qrand() % 2))
        {
        }
    }
}

bool GameScene::placeCannon(qreal x, qreal y, qreal dir)
{
    bool success = false;
    Cannon* cannonToPlace = new Cannon();
    cannonToPlace->setPos(QPointF(x, y));
    addItem(cannonToPlace);
    if (!collidingItems(cannonToPlace).isEmpty())
    {
        removeItem(cannonToPlace);
        delete cannonToPlace;
    }
    else
    {
        success = true;
        cannonToPlace->setData(0, "cannon");
        cannonToPlace->setDirection(dir);
        cannons.append(cannonToPlace);
    }
    return success;
}

Bullet *GameScene::makeShot(Cannon* cannon)
{
    cannon->setShots(cannon->getShots() + 1);
    Bullet* bullet = new Bullet(cannon);
    bullets.append(bullet);
    addItem(bullet);
    bullet->setX(cannon->x());
    bullet->setY(cannon->y());
    bullet->setDirection(cannon->getDirection());
    bullet->setSpeed(5);
    bullet->setData(0, "bullet");
    stats();
    return bullet;
}

void GameScene::stats()
{
    QString msg;
    msg.append("number of your shots:").
            append(QString::number(cannon->getShots())).
            append("; number of enemies:").
            append(QString::number(numberOfEnemies)).
            append("; number of destroyed enemies:").
            append(QString::number(numberOfEnemies - cannons.size()));
    statsItem->setPlainText(msg);
    statsItem->setData(1, cannon->getShots());
    statsItem->setData(2, cannons.size());
    statsItem->update(statsItem->boundingRect());
}

void GameScene::showWinner(bool winner)
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Winner");
    QString msg(winner ?
                    "          You win!!!          " :
                    "          You lose :(         ");
    msg.append("\nnumber of your shots:").
            append(QString::number(statsItem->data(1).toInt())).
            append("\nnumber of enemies:").
            append(QString::number(numberOfEnemies)).
            append("\nnumber of destroyed enemies:").
            append(QString::number(numberOfEnemies - statsItem->data(2).toInt()));
    msgBox.setText(msg);
    msgBox.exec();
}

void GameScene::processCollisions()
{
    foreach (Bullet *bullet, bullets)
    {
        QList<QGraphicsItem*> collisionsList = collidingItems(bullet);
        bool exist = true;
        foreach (QGraphicsItem * item, collisionsList)
        {
            qDebug() << item->data(0).toString();
            if (item != bullet)
            {
                if ((item->data(0) == "cannon")
                        && (item != bullet->getOwner())
                        && (bullet->getOwner()->getColor() != static_cast<Cannon*>(item)->getColor())//teams
                        )
                {
                    removeItem(item);
                    if ((!cannons.removeOne(static_cast<Cannon*>(item))) || cannons.isEmpty())
                    {
                        stats();
                        showWinner(cannons.isEmpty());
                        startGame(cannons.isEmpty() ? 1 : 0);
                        return;
                    }
                    exist = false;
                }
                else if (item->data(0) == "bullet")
                {
                    removeItem(item);
                    bullets.removeOne(static_cast<Bullet*>(item));
                    exist = false;
                }
                else if ((item->data(0) == "ground")
                         || (item->data(0) == "mountain")
                         || (item->data(0) == "wall"))
                {
                    exist = false;
                }
            }
        }
        if (!exist)
        {
            removeItem(bullet);
            bullets.removeOne(bullet);
        }
    }
}

void GameScene::otherCannonsShot()
{
    foreach (Cannon *can, cannons)
    {
        if ((qrand() % 100) <= 5)
        {
            //AI
            qreal ang = 360 * atan((cannon->y() - can->y())/(can->x() - cannon->x())) / (2 * 3.14);
            if (cannon->x() < can->x())
            {
                can->setDirection(1);
                can->setAngle(ang);
            }
            else
            {
                can->setDirection(0);
                can->setAngle(-ang);
            }
            can->update(can->boundingRect());
            //
            makeShot(can);
        }
    }
}

void GameScene::phisics(Cannon *can)
{
    qDebug() << "phisics";
    QList<QGraphicsItem*> collisionsList;
    while (!isOnSurface(can))
    {
        qDebug() << "wh1";
        QPointF delta(0, 1);
        can->setPos(can->mapToParent(delta));
        qDebug() << can->x() << " " << can->y();
        qDebug() << "wh2";
    }
    collisionsList = collidingItems(can);
    foreach (QGraphicsItem * item, collisionsList)
    {
        qDebug() << "physics " << item->data(0).toString();
        if (item != can)
        {
            if (item->data(0) == "mountain")
            {
                while (can->collidesWithItem(item))
                {
                    QPointF delta(0, -1);
                    can->setPos(can->mapToParent(delta));
                    qDebug() << can->x() << " " << can->y();
                }
            }
            else if (item->data(0) == "wall")
            {
                while (can->collidesWithItem(item))
                {
                    int dx = 0;
                    if (can->x() > item->x())
                    {
                        dx = 1;
                    }
                    else if (can->x() < item->x())
                    {
                        dx = -1;
                    }
                    QPointF delta(dx, 0);
                    can->setPos(can->mapToParent(delta));
                }
            }
        }
    }
    qDebug() << "phisics: ends";
}

bool GameScene::isOnSurface(Cannon *can)
{
    foreach (QGraphicsItem* item, collidingItems(can))
    {
        if ((item->data(0) == "ground") || (item->data(0) == "mountain"))
        {
            return true;
        }
    }
    return false;
}

void GameScene::keyPressEvent(QKeyEvent *event)
{
    QPointF delta(0, 0);
    switch (event->key())
    {
        case Qt::Key_Left:
            delta.setX(-3);
            if (cannon->getDirection() != 1)
            {
                cannon->setDirection(1);
                cannon->update(cannon->boundingRect());
            }
            break;
        case Qt::Key_Right:
            delta.setX(3);
            if (cannon->getDirection() != 0)
            {
                cannon->setDirection(0);
                cannon->update(cannon->boundingRect());
            }
            break;
        case Qt::Key_Space:
            makeShot(cannon);
            break;
        case Qt::Key_Up:
            if (!((cannon->getAngle() - 2 > -91) && (cannon->getAngle() - 2 < -89)))
            {
                cannon->setAngle(cannon->getAngle() - 2);
                cannon->update(cannon->boundingRect());
            }
            break;
        case Qt::Key_Down:
            if (!((cannon->getAngle() + 2 > 89) && (cannon->getAngle() + 2 < 91)))
            {
                cannon->setAngle(cannon->getAngle() + 2);
                cannon->update(cannon->boundingRect());
            }
            break;
        case Qt::Key_F1:
            help();
            break;
        case Qt::Key_F5:
            startGame(0);
            break;
        default:
            break;
    }
    if (delta.x() || delta.y())
    {
        cannon->setPos(cannon->mapToParent(delta));
        phisics(cannon);
    }
    foreach (Cannon* can, cannons)
    {
        phisics(can);
    }
}

void GameScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
{
    if (mouseEvent->button())
    {
        qreal ang = 360
                * atan((mouseEvent->scenePos().y() - cannon->y())
                       /(cannon->x() - mouseEvent->scenePos().x()))
                / (2 * 3.14);
        if (mouseEvent->scenePos().x() < cannon->x())
        {
            cannon->setDirection(1);
            cannon->setAngle(ang);
        }
        else
        {
            cannon->setDirection(0);
            cannon->setAngle(-ang);
        }
        cannon->update(cannon->boundingRect());
        makeShot(cannon);
    }
}

void GameScene::help()
{
    QMessageBox helpBox;
    helpBox.setWindowTitle("Help");
    helpBox.setText("arrows left and right - movement\n"
                    "arrows up and down - changing guns angle\n"
                    "space - make shot\n"
                    "F1 - this help\n"
                    "F5 - restart this level\n"
                    "UPD: mouse click - shot in point");
    helpBox.exec();
}

void GameScene::startGame(int dNumber)
{
    numberOfEnemies += dNumber;
    clear();
    genLandscape();
    bullets.clear();
    cannons.clear();
    placeCannons(numberOfEnemies);
    cannon = new Cannon();
    addItem(cannon);
    cannon->setX(47.5);
    cannon->setY(430);
    cannon->setColor(Qt::green);
    cannon->setData(0, "cannon");
    phisics(cannon);
    foreach (Cannon* can, cannons)
    {
        phisics(can);
    }
    statsItem = new QGraphicsTextItem();
    addItem(statsItem);
    statsItem->setPos(0, 0);
    statsItem->setData(0, "stats");
    stats();
}
