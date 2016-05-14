#include "calculatorwidget.h"
#include "ui_calculatorwidget.h"

CalculatorWidget::CalculatorWidget(QWidget *parent) :
    QWidget(parent), ui(new Ui::CalculatorWidget)
{
    ui->setupUi(this);
    digitsSignalMapper = new QSignalMapper(this);
    connect(ui->button0, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button0, 0);
    connect(ui->button1, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button1, 1);
    connect(ui->button2, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button2, 2);
    connect(ui->button3, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button3, 3);
    connect(ui->button4, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button4, 4);
    connect(ui->button5, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button5, 5);
    connect(ui->button6, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button6, 6);
    connect(ui->button7, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button7, 7);
    connect(ui->button8, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button8, 8);
    connect(ui->button9, SIGNAL(pressed()), digitsSignalMapper, SLOT(map()));
    digitsSignalMapper->setMapping(ui->button9, 9);

    connect(digitsSignalMapper, SIGNAL(mapped(int)), this, SLOT(numberPressed(int)));

    opsSignalMapper = new QSignalMapper(this);
    connect(ui->buttonSum, SIGNAL(pressed()), opsSignalMapper, SLOT(map()));
    opsSignalMapper->setMapping(ui->buttonSum, 0);
    connect(ui->buttonMinus, SIGNAL(pressed()), opsSignalMapper, SLOT(map()));
    opsSignalMapper->setMapping(ui->buttonMinus, 1);
    connect(ui->buttonMult, SIGNAL(pressed()), opsSignalMapper, SLOT(map()));
    opsSignalMapper->setMapping(ui->buttonMult, 2);
    connect(ui->buttonDiv, SIGNAL(pressed()), opsSignalMapper, SLOT(map()));
    opsSignalMapper->setMapping(ui->buttonDiv, 3);

    connect(opsSignalMapper, SIGNAL(mapped(int)), this, SLOT(opPressed(int)));

    connect(ui->buttonDot, SIGNAL(pressed()), this, SLOT(dotPressed()));
    connect(ui->buttonEqual, SIGNAL(pressed()), this, SLOT(equalPressed()));
    connect(ui->strField, SIGNAL(returnPressed()), this, SLOT(clearField()));

    this->setLayout(ui->gridLayout);
    //
    calc = new Calculator<PointerStack<TokenStruct>, PointerStack<double>>;
}

CalculatorWidget::~CalculatorWidget()
{
    delete ui;
}

void CalculatorWidget::numberPressed(int number)
{
    ui->strField->setText(ui->strField->text() + QString::number(number));
}

void CalculatorWidget::opPressed(int op)
{
    QString oper = "+";
    if (!op)
    {
        oper = "+";
    }
    else if (op == 1)
    {
        oper = "-";
    }
    else if (op == 2)
    {
        oper = "*";
    }
    else if (op == 3)
    {
        oper = "/";
    }
    ui->strField->setText(ui->strField->text() + oper);
}

void CalculatorWidget::dotPressed()
{
    ui->strField->setText(ui->strField->text() + ".");
}

void CalculatorWidget::equalPressed()
{
    qDebug("eq");
    calc->operator()(ui->strField->text().toUtf8().data());
    ui->strField->setText(QString::number(calc->compute()));
}

void CalculatorWidget::clearField()
{
    qDebug("clr");
    ui->strField->setText("");
}
