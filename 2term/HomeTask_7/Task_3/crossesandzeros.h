#pragma once

#include <QWidget>
#include <QMap>
#include <QPushButton>

namespace Ui {
class CrossesAndZeros;
}

class CrossesAndZeros : public QWidget
{
    Q_OBJECT

public:
    explicit CrossesAndZeros(QWidget *parent = 0);
    ~CrossesAndZeros();

private slots:
    void generateField();
    void buttonClicked();
private:
    bool findWinner(unsigned int pos, unsigned int player);
    void computersTurn();
    bool isPart(int i, int j, unsigned int player);
    Ui::CrossesAndZeros *ui;

    unsigned int currentSize;
    unsigned int turn;
    QMap<QPushButton*, unsigned int> field;
};
