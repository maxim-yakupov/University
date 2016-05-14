#pragma once
#include <QGraphicsItem>

class Cannon : public QGraphicsItem
{
public:
    Cannon(QGraphicsItem* parent = 0);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter,
                       const QStyleOptionGraphicsItem *option,
                       QWidget *widget);
    qreal getDirection();
    void setDirection(qreal dir);
    qreal getAngle();
    void setAngle(qreal ang);
    int getShots();
    void setShots(int n);
    QColor getColor();
    void setColor(QColor col);
private:
    qreal direction;
    qreal angle;
    int shots;
    QColor color;
};
