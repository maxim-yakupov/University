#include "field.h"

#include <QPainter>

Field::Field(QGraphicsItem *parent, int width, int height) : QGraphicsItem(parent),
    width(width), height(height)
{
    matrix = new Tile**[height];
    for (int i = 0; i < height; i++)
    {
        matrix[i] = new Tile*[width];
        for (int j = 0; j < width; j++)
        {
            matrix[i][j] = new Tile(this, Tile::NONE);
            matrix[i][j]->setPos(j * (GameParams::tileSize + 1), i * (GameParams::tileSize + 1));
        }
    }
}

Field::~Field()
{
    for (int i = 0; i < height; i++)
    {
        delete[] matrix[i];
    }
}

QRectF Field::boundingRect() const
{
    return QRectF(0, 0,
                  GameParams::tileSize * width, GameParams::tileSize * height);
}

QPainterPath Field::shape() const
{
    QPainterPath path;
    path.addRect(0, 0,
                 GameParams::tileSize * width, GameParams::tileSize * height);
    return path;
}

void Field::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->setBrush(QColor(128, 128, 128));
    painter->setPen(Qt::NoPen);
    painter->drawRect(boundingRect());
}

Tile *Field::getTile(int x, int y)
{
    return matrix[y][x];
}

int Field::getWidth()
{
    return width;
}

int Field::getHeight()
{
    return height;
}

bool Field::isWalkable(int x, int y)
{
    if (x >= 0 && x < width && y >=0 && y < height)
    {
        Tile* tile = getTile(x, y);
        return tile->getType() != Tile::WALL && !tile->isBoxOn();
    }
    return false;
}

void Field::lookAfter(Tile *tile)
{
    buttons.insert(tile);
}

bool Field::checkWin()
{
    foreach (Tile* tile, buttons)
    {
        if (!tile->isBoxOn())
        {
            return false;
        }
    }
    return true;
}
