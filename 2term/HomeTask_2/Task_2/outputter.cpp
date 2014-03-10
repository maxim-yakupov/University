#include "outputter.h"

Outputter::Outputter()
{
}

Outputter::~Outputter()
{
}

int *Outputter::bypass(int **array, unsigned int size)
{
    enum Direction
    {
        up,
        right,
        down,
        left
    };
    Direction direction = up;

    struct Decart
    {
        unsigned int x;
        unsigned int y;
    };
    Decart position = {0, 0};
    position.x = size / 2;
    position.y = position.x;

    int* result = new int[size*size];
    for (unsigned int i = 0; i < size*size; i++)
    {
        result[i] = array[position.y][position.x];
        switch (direction)
        {
        case up:
            position.y--;
            if (position.x - 1 == position.y) direction = right;
            break;
        case right:
            position.x++;
            if (size - position.x - 1 == position.y) direction = down;
            break;
        case down:
            position.y++;
            if (position.x == position.y) direction = left;
            break;
        case left:
            position.x--;
            if (size - position.x - 1 == position.y) direction = up;
            break;
        default:
            break;
        }
    }
    return result;
}
