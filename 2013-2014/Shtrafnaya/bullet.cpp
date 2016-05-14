#include "bullet.h"
#include <QPainter>

Bullet::Bullet(Cannon *parent) : direction(0),
    angle(parent->getAngle()),
    speed(0),
    owner(parent),
    color(parent->getColor())
{
}

QRectF Bullet::boundingRect() const
{
    return QRectF(-3, -3, 6, 6);
}

QPainterPath Bullet::shape() const
{
    QPainterPath path;
    path.addEllipse(-2, -2, 4, 4);
    return path;
}

void Bullet::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(color);
    painter->setPen(Qt::NoPen);
    painter->drawEllipse(-2, -2, 4, 4);
}

qreal Bullet::getDirection()
{
    return direction;
}

void Bullet::setDirection(qreal dir)
{
    direction = dir;
}

qreal Bullet::getSpeed()
{
    return speed;
}

void Bullet::setSpeed(qreal s)
{
    speed = s;
}

Cannon *Bullet::getOwner()
{
    return owner;
}

void Bullet::advance(int step)
{
    const qreal pi = 3.14;
    if (!step)
    {
        return;
    }
    int mult = 1;
    if (direction)
    {
        mult = -1;
    }
    qreal rad = angle * 2* pi / 360;
    setPos(mapToParent(mult * speed * cos(rad),
                       speed * sin(rad)));
}
