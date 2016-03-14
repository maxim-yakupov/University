#include "player.h"

#include <QPainter>

Player::Player(QGraphicsItem *parent, int x, int y) : QGraphicsItem(parent),
    x(x), y(y), direction(STAY)
{
}

QRectF Player::boundingRect() const
{
    return QRectF(0, 0,
                  GameParams::tileSize + 2, GameParams::tileSize + 2);
}

QPainterPath Player::shape() const
{
    QPainterPath path;
    path.addRect(0, 0,
                 GameParams::tileSize, GameParams::tileSize);
    return path;
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRect rect(0, 0,
               GameParams::tileSize, GameParams::tileSize);
    painter->drawPixmap(rect, QPixmap(":/img/player.png"));
    setZValue(2);
}
int Player::getX() const
{
    return x;
}

void Player::setX(int value)
{
    x = value;
}
int Player::getY() const
{
    return y;
}

void Player::setY(int value)
{
    y = value;
}
Player::Direction Player::getDirection() const
{
    return direction;
}

void Player::setDirection(const Direction &value)
{
    direction = value;
}



