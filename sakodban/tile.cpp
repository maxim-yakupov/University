#include "tile.h"

#include <QPainter>

Tile::Tile(QGraphicsItem *parent, Tile::TileType type) : QGraphicsItem(parent),
    type(type), boxOn(false)
{
}

QRectF Tile::boundingRect() const
{
    return QRectF(0, 0,
                  GameParams::tileSize + 2, GameParams::tileSize + 2);
}

QPainterPath Tile::shape() const
{
    QPainterPath path;
    path.addRect(0, 0,
                 GameParams::tileSize, GameParams::tileSize);
    return path;
}

void Tile::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    QRect rect(0, 0,
               GameParams::tileSize, GameParams::tileSize);
    if (boxOn)
    {
        painter->drawPixmap(rect, QPixmap(":/img/chest.png"));
        return;
    }
    switch (type) {
    case NONE:
        break;
    case WALL:
        {
            QRect r(rect.x() - 1, rect.y() - 1, rect.width() + 2, rect.height() + 2);
            painter->drawPixmap(r, QPixmap(":/img/wall.png"));
        };
        break;
    case BUTTON:
        painter->drawPixmap(rect, QPixmap(":/img/button.png"));
        break;
    default:
        break;
    }
}

Tile::TileType Tile::getType()
{
    return type;
}

void Tile::setType(Tile::TileType type)
{
    this->type = type;
}

bool Tile::isBoxOn()
{
    return boxOn;
}

void Tile::putBox()
{
    boxOn = true;
    update(boundingRect());
}

void Tile::removeBox()
{
    boxOn = false;
    update(boundingRect());
}
