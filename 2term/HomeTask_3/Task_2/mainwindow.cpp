#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->comboBox->addItem("+", 0);
    ui->comboBox->addItem("-", 1);
    ui->comboBox->addItem("*", 2);
    ui->comboBox->addItem("/", 3);
    ui->comboBox->addItem("%", 4);
    compute();
    connect(ui->spinBox, SIGNAL(valueChanged(int)), this, SLOT(checkForDivisionByZero()));
    connect(ui->spinBox_2, SIGNAL(valueChanged(int)), this, SLOT(checkForDivisionByZero()));
    connect(ui->comboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(checkForDivisionByZero()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::compute()
{
    int result = ui->spinBox->value();
    if (ui->comboBox->currentIndex() == 0)
    {
        result += ui->spinBox_2->value();
    }
    else if (ui->comboBox->currentIndex() == 1)
    {
        result -= ui->spinBox_2->value();
    }
    else if (ui->comboBox->currentIndex() == 2)
    {
        result *= ui->spinBox_2->value();
    }
    else if (ui->comboBox->currentIndex() == 3)
    {
        result /= ui->spinBox_2->value();
    }
    else if (ui->comboBox->currentIndex() == 4)
    {
        result %= ui->spinBox_2->value();
    }
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

void MainWindow::checkForDivisionByZero()
{
    if (ui->comboBox->currentIndex() > 2 && ui->spinBox_2->value() == 0)
    {
        ui->lineEdit->setText("division by zero!");
    }
    else
    {
        compute();
    }
}
