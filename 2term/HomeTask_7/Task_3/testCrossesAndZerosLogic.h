#pragma once

#include <QtTest/QTest>
#include <QtCore/QObject>

#include "crossesandzeroslogicpv.h"

class TestCrossesAndZerosLogic : public QObject
{
    Q_OBJECT
public:
    explicit TestCrossesAndZerosLogic(QObject *parent = 0) : QObject(parent) {}
private slots:
    void gameBeginningCheckForWin()
    {
        CrossesAndZerosLogicPV logicCZ;
        QCOMPARE(logicCZ.findWinner(0, 1), false);
        QCOMPARE(logicCZ.findWinner(0, 2), false);
    }
    void gamePlayerWinCheckForWin()
    {
        CrossesAndZerosLogicPV logicCZ;
        logicCZ.field[0][0] = 1;
        logicCZ.field[1][1] = 1;
        logicCZ.field[2][2] = 1;
        QCOMPARE(logicCZ.findWinner(8, 1), true);
        QCOMPARE(logicCZ.findWinner(8, 2), false);
    }
    void gameCompWinCheckForWin()
    {
        CrossesAndZerosLogicPV logicCZ;
        logicCZ.field[0][2] = 2;
        logicCZ.field[1][1] = 2;
        logicCZ.field[2][0] = 2;
        QCOMPARE(logicCZ.findWinner(6, 1), false);
        QCOMPARE(logicCZ.findWinner(6, 2), true);
    }
    void checkWrongCoords()
    {
        CrossesAndZerosLogicPV logicCZ;
        logicCZ.field[0][0] = 1;
        logicCZ.field[0][1] = 2;
        logicCZ.field[0][2] = 1;
        logicCZ.field[1][0] = 2;
        logicCZ.field[1][1] = 1;
        logicCZ.field[1][2] = 2;
        logicCZ.field[2][0] = 1;
        logicCZ.field[2][1] = 2;
        logicCZ.field[2][2] = 1;
        //ok
        QCOMPARE(logicCZ.isPart(0, 0, 1), true);
        QCOMPARE(logicCZ.isPart(0, 1, 2), true);
        QCOMPARE(logicCZ.isPart(0, 2, 1), true);
        QCOMPARE(logicCZ.isPart(1, 0, 2), true);
        QCOMPARE(logicCZ.isPart(1, 1, 1), true);
        QCOMPARE(logicCZ.isPart(1, 2, 2), true);
        QCOMPARE(logicCZ.isPart(2, 0, 1), true);
        QCOMPARE(logicCZ.isPart(2, 1, 2), true);
        QCOMPARE(logicCZ.isPart(2, 2, 1), true);
        //wrong
        QCOMPARE(logicCZ.isPart(-1, 0, 1), false);
        QCOMPARE(logicCZ.isPart(0, -1, 1), false);
        QCOMPARE(logicCZ.isPart(-1, 0, 2), false);
        QCOMPARE(logicCZ.isPart(0, -1, 2), false);
        QCOMPARE(logicCZ.isPart(3, 3, 1), false);
        QCOMPARE(logicCZ.isPart(3, 3, 2), false);
        QCOMPARE(logicCZ.isPart(2, 0, 2), false);
        QCOMPARE(logicCZ.isPart(0, 2, 2), false);
    }
};
