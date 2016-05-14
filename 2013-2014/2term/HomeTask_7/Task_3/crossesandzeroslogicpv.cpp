#include <QtDebug>
#include <QMessageBox>
#include "time.h"
#include "crossesandzeroslogicpv.h"

CrossesAndZerosLogicPV::CrossesAndZerosLogicPV(unsigned int size) :
    size(size),
    turn(0)
{
    qsrand(time(nullptr));

    field = new unsigned int*[size];
    for (unsigned int i = 0; i < size; i++)
    {
        field[i] = new unsigned int[size];
        for (unsigned int j = 0; j < size; j++)
        {
            field[i][j] = 0;
        }
    }
}

CrossesAndZerosLogicPV::~CrossesAndZerosLogicPV()
{
    for (unsigned int i = 0; i < size; i++)
    {
        delete [] field[i];
    }
    delete [] field;
}

void CrossesAndZerosLogicPV::playersTurn(unsigned int pos)
{
    qDebug("playersTurn begins");
    field[pos / size][pos % size] = 1;
    turn++;
    emit turnMade(turn);
    bool userWin = findWinner(pos, 1);
    qDebug("win checked");
    qDebug() << userWin;
    if (!userWin && (size * size != turn))
    {
        qDebug("comps turn");
        computersTurn();
    }
    else if (userWin)
    {
        showMessage(1);
        emit restart();
    }
    else
    {
        showMessage(0);
        emit restart();
    }
    qDebug("playersTurn ends");
}

bool CrossesAndZerosLogicPV::isPart(int i, int j, unsigned int player)
{
    qDebug() << "isPart " << i << " " << j;
    return ((i >= 0) && (i < static_cast<int>(size))
            && (j >= 0) && (j < static_cast<int>(size))
            && (field[i][j] == player));
}

///GUI deleted
void CrossesAndZerosLogicPV::showMessage(unsigned int winner)
{
    Q_UNUSED(winner);
}

bool CrossesAndZerosLogicPV::findWinner(unsigned int pos, unsigned int player)
{
    qDebug("findWinner begins");
    bool win = false;
    int i = pos / size;
    int j = pos % size;
    qDebug() << i << " " << j;
    //vertical
    if (isPart(i - 1, j, player))
    {
        if (isPart(i - 2, j, player) || isPart(i + 1, j, player))
        {
            win = true;
        }
    }
    if (isPart(i + 1, j, player) && isPart(i + 2, j, player))
    {
        win = true;
    }
    //horisontal
    if (isPart(i, j - 1, player))
    {
        if (isPart(i, j - 2, player) || isPart(i, j + 1, player))
        {
            win = true;
        }
    }
    if (isPart(i, j + 1, player) && isPart(i, j + 2, player))
    {
        win = true;
    }
    //diag1
    if (isPart(i - 1, j - 1, player))
    {
        if (isPart(i - 2, j - 2, player) || isPart(i + 1, j + 1, player))
        {
            win = true;
        }
    }
    if (isPart(i + 1, j + 1, player) && isPart(i + 2, j + 2, player))
    {
        win = true;
    }
    //diag2
    if (isPart(i - 1, j + 1, player))
    {
        if (isPart(i - 2, j + 2, player) || isPart(i + 1, j - 1, player))
        {
            win = true;
        }
    }
    if (isPart(i + 1, j - 1, player) && isPart(i + 2, j - 2, player))
    {
        win = true;
    }
    qDebug("findWinner ends");
    return win;
}

void CrossesAndZerosLogicPV::computersTurn()
{
    qDebug("comps turn begins");
    unsigned int pos = 0;
    do
    {
        qDebug() << "ct!" << pos;
        pos = qrand() % (size * size);
    } while (field[pos / size][pos % size]);

    qDebug("button found");
    qDebug() << field[pos / size][pos % size];
    emit cellChanged(pos, 2, false);
    field[pos / size][pos % size] = 2;
    turn++;
    emit turnMade(turn);

    bool compWin = findWinner(pos, 2);
    qDebug("win checked");
    qDebug() << compWin;
    if (!compWin && (size * size != turn))
    {
    }
    else if (compWin)
    {
        showMessage(2);
        emit restart();
    }
    else
    {
        showMessage(0);
        emit restart();
    }
    qDebug("comps turn ends");
}
