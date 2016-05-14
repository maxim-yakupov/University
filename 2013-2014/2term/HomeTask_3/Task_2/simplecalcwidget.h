#ifndef SIMPLECALCWIDGET_H
#define SIMPLECALCWIDGET_H

#include <QWidget>
#include "simplecalc.h"

namespace Ui {
class SimpleCalcWidget;
}

/**
 * @brief The SimpleCalcWidget class
 * @detailed Placing of calculator widget's components & calculate slot setting
 */
class SimpleCalcWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SimpleCalcWidget(QWidget *parent = 0);
    virtual ~SimpleCalcWidget();
public slots:
    /**
     * @brief calculate Calculates expression from calculator widget form
     */
    void calculate();
private:
    Ui::SimpleCalcWidget *ui;
    SimpleCalc* calculator;
};

#endif // SIMPLECALCWIDGET_H
