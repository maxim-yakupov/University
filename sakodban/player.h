#pragma once

#include <QGraphicsItem>

#include "gameParams.h"

class Player : public QGraphicsItem
{
public:
    enum Direction {
        STAY,
        LEFT,
        UP,
        RIGHT,
        DOWN
    };

    Player(QGraphicsItem* parent = 0, int x = 0, int y = 0);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
               const QStyleOptionGraphicsItem *option,
               QWidget *widget);
    int getX() const;
    void setX(int value);

    int getY() const;
    void setY(int value);

    Direction getDirection() const;
    void setDirection(const Direction &value);

private:
    int x;
    int y;
    Direction direction;
};
