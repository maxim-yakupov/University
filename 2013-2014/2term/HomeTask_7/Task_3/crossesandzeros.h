#pragma once

#include <QWidget>
#include <QMap>
#include <QPushButton>

#include "crossesandzeroslogic.h"

namespace Ui {
class CrossesAndZeros;
}

class CrossesAndZeros : public QWidget
{
    Q_OBJECT

public:
    explicit CrossesAndZeros(QWidget *parent = 0);
    ~CrossesAndZeros();
signals:
    /**
     * @brief playersTurnW Emits, when clicked button become disabled
     */
    void playersTurnW(unsigned int);
public slots:
    /**
     * @brief printTurn Changing turns-counter on form
     */
    void printTurn(unsigned int);
    /**
     * @brief buttonClicked Processes user's click on some button in the game field
     */
    void buttonClicked();
    /**
     * @brief generateField Generates empty field of buttons
     */
    void generateField();
    /**
     * @brief setButton Changing state of some button in the game field
     */
    void setButton(unsigned int, unsigned int, bool);
private:
    Ui::CrossesAndZeros *ui;

    CrossesAndZerosLogic *logic;

    unsigned int currentSize;

    QMap<unsigned int, QPushButton*> field;
};
