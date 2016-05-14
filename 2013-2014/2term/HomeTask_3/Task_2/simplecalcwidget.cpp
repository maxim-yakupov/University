#include "simplecalcwidget.h"
#include "ui_simplecalcwidget.h"

SimpleCalcWidget::SimpleCalcWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::SimpleCalcWidget), calculator(new SimpleCalc)
{
    ui->setupUi(this);

    ui->comboBox->addItem("+", 0);
    ui->comboBox->addItem("-", 1);
    ui->comboBox->addItem("*", 2);
    ui->comboBox->addItem("/", 3);
    ui->comboBox->addItem("%", 4);

    this->setLayout(ui->calcLayoutW);//layout linked with mainWindow

    calculate();

    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(calculate()));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(calculate()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(calculate()));
}

SimpleCalcWidget::~SimpleCalcWidget()
{
    delete calculator;
    delete ui;
}

void SimpleCalcWidget::calculate()
{
    if (ui->comboBox->currentIndex() > 2 && ui->spinBox_2->value() == 0)
    {
        ui->lineEdit->setText("division by zero!");
    }
    else
    {
        int result = calculator->compute(ui->spinBox->value(), ui->spinBox_2->value(), ui->comboBox->currentIndex());
        QString resultStr = "";
        bool minus = (result < 0);
        result = abs(result);
        resultStr += (result % 10 + '0');
        result /= 10;
        while (result)
        {
            resultStr = (result % 10 + '0') + resultStr;
            result /= 10;
        }
        if (minus)
        {
            resultStr = '-' + resultStr;
        }
        ui->lineEdit->setText(resultStr);
    }
}
