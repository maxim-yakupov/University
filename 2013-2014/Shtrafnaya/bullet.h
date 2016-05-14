#pragma once
#include <QGraphicsItem>
#include "cannon.h"

class Bullet : public QGraphicsItem
{
public:
    Bullet(Cannon* parent);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    qreal getDirection();
    void setDirection(qreal dir);
    qreal getSpeed();
    void setSpeed(qreal s);
    Cannon* getOwner();
protected:
    void advance(int step);
private:
    qreal direction;
    qreal angle;
    qreal speed;
    Cannon* owner;
    QColor color;
};
