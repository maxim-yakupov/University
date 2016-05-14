#include "widget.h"
#include "ui_widget.h"
#include <QTimer>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->pushButton, SIGNAL(clicked()), &timer, SLOT(start()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(incProgress()));
}

Widget::~Widget()
{
    delete ui;
}

void Widget::incProgress()
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
    if (ui->progressBar->value() == 100)
    {
        timer.stop();
        disconnect(&timer, SIGNAL(timeout()), this, SLOT(incProgress()));
        disconnect(ui->pushButton, SIGNAL(clicked()), &timer, SLOT(start()));
        ui->pushButton->setText("Закрыть");
        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(close()));
    }
}
