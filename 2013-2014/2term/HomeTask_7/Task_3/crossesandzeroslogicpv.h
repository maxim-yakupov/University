#pragma once

#include <QWidget>

/// version of class CrossesAndZerosLogic for test
/// (all methods and fields are public, inherited from QObject[without GUI])
class CrossesAndZerosLogicPV : public QObject
{
    Q_OBJECT

public:
    explicit CrossesAndZerosLogicPV(unsigned int size = 3);
    ~CrossesAndZerosLogicPV();
    /**
     * @brief findWinner Checks 'player's win
     * @param pos Changed position
     * @param player '1' if player, '2' if computer
     * @return true if win, false if not
     */
    bool findWinner(unsigned int pos, unsigned int player);
    /**
     * @brief computersTurn Processes computer's turn
     */
    void computersTurn();
    /**
     * @brief isPart Checks if cell in field & marked with 'player' value
     * @param i First coord
     * @param j Second coord
     * @param player '1' if player, '2' if computer
     * @return true if condition Ok, false if not
     */
    bool isPart(int i, int j, unsigned int player);
    /**
     * @brief showMessage Shows message in the end of game
     * @param winner '1' if player, '2' if computer. '0' if draw
     */
    void showMessage(unsigned int winner);

    unsigned int size;
    unsigned int turn;

    unsigned int **field;
signals:
    /**
     * @brief cellChanged Emits, when cell state changing
     */
    void cellChanged(unsigned int, unsigned int, bool);
    /**
     * @brief turnMade Emits, when turns counter changed
     */
    void turnMade(unsigned int);
    /**
     * @brief restart Emits, when game is over & we want new game
     */
    void restart();
public slots:
    /**
     * @brief playersTurn Processes player's turn & decides what will be next: computer's turn or end of game
     */
    void playersTurn(unsigned int);
};
