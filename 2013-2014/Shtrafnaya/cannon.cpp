#include "cannon.h"
#include <QPainter>

Cannon::Cannon(QGraphicsItem *parent) : QGraphicsItem(parent),
    direction(0),
    angle(0),
    shots(0),
    color(Qt::white)
{
}

QRectF Cannon::boundingRect() const
{
    return QRectF(-30, -30, 60, 60);
}

QPainterPath Cannon::shape() const
{
    QPainterPath path;
    path.addEllipse(-7.5, -5, 15, 15);
    return path;
}

void Cannon::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    const qreal pi = 3.14;
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    int mult = 1;
    if (direction)
    {
        mult = -1;
    }
    //body
    painter->drawEllipse(-7.5, -5, 15, 15);
    //gun
    qreal rad = angle * 2 * pi / 360;
    QPen pen;
    pen.setColor(color);
    pen.setWidth(6);
    painter->setPen(pen);
    QLineF gun;
    gun.setP1(QPointF(0, 0));
    gun.setP2(QPointF(25 * mult * cos(rad), 25 * sin(rad)));
    painter->drawLine(gun);
}

qreal Cannon::getDirection()
{
    return direction;
}

void Cannon::setDirection(qreal dir)
{
    direction = dir;
}

qreal Cannon::getAngle()
{
    return angle;
}

void Cannon::setAngle(qreal ang)
{
    if (ang >= 360)
    {
        ang -= 360;
    }
    else if (ang <= -360)
    {
        ang += 360;
    }
    angle = ang;
}

int Cannon::getShots()
{
    return shots;
}

void Cannon::setShots(int n)
{
    shots = n;
}

QColor Cannon::getColor()
{
    return color;
}

void Cannon::setColor(QColor col)
{
    color = col;
}
