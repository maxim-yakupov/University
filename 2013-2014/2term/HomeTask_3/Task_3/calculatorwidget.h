#ifndef CALCULATORWIDGET_H
#define CALCULATORWIDGET_H

#include <QWidget>
#include <QSignalMapper>
#include "calculator.h"

namespace Ui {
class CalculatorWidget;
}

class CalculatorWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CalculatorWidget(QWidget *parent = 0);
    ~CalculatorWidget();

private slots:
    void numberPressed(int number);
    void opPressed(int op);
    void dotPressed();
    void equalPressed();
    void clearField();

private:
    Ui::CalculatorWidget *ui;
    QSignalMapper *digitsSignalMapper;
    QSignalMapper *opsSignalMapper;
    Calculator<PointerStack<TokenStruct>, PointerStack<double>> *calc;
};

#endif // CALCULATORWIDGET_H
