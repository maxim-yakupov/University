#ifndef SIMPLECALCWIDGET_H
#define SIMPLECALCWIDGET_H

#include <QWidget>
#include "simplecalc.h"

namespace Ui {
class SimpleCalcWidget;
}

class SimpleCalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleCalcWidget(QWidget *parent = 0);
    virtual ~SimpleCalcWidget();
public slots:
    void calculate();
private:
    Ui::SimpleCalcWidget *ui;
    SimpleCalc* calculator;
};

#endif // SIMPLECALCWIDGET_H
