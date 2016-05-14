#pragma once

#include <QGraphicsItem>
#include <QSet>

#include "tile.h"

class Field : public QGraphicsItem
{
public:
    Field(QGraphicsItem* parent = 0, int width = 10, int height = 10);
    ~Field();

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    Tile* getTile(int x, int y);
    int getWidth();
    int getHeight();
    bool isWalkable(int x, int y);
    // adds tile in buttons set
    void lookAfter(Tile* tile);
    bool checkWin();
private:
    int width;
    int height;

    QSet<Tile*> buttons;
    Tile*** matrix;
};
