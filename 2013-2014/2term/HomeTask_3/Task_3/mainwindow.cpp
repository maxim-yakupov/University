#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calculatorwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CalculatorWidget* calculator = new CalculatorWidget(this);
    this->setCentralWidget(calculator);
}

MainWindow::~MainWindow()
{
    delete ui;
}
