#pragma once

#include <QGraphicsItem>

#include "gameParams.h"

class Tile : public QGraphicsItem
{
public:
    enum TileType {
        NONE,
        WALL,
        BUTTON
    };

    Tile(QGraphicsItem* parent = 0, TileType type = TileType::NONE);

    QRectF boundingRect() const;
    QPainterPath shape() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    TileType getType();
    void setType(TileType type);
    bool isBoxOn();
    void putBox();
    void removeBox();
private:
    TileType type;
    bool boxOn;
};
