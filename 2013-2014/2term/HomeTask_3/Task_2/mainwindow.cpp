#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "simplecalcwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SimpleCalcWidget* wdgt = new SimpleCalcWidget(this);
    this->setCentralWidget(wdgt);
}

MainWindow::~MainWindow()
{
    delete ui;
}
