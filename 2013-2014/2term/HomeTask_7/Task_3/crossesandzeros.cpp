#include <QtDebug>
#include <QMessageBox>
#include "crossesandzeros.h"
#include "ui_crossesandzeros.h"

CrossesAndZeros::CrossesAndZeros(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CrossesAndZeros),
    currentSize(0)
{
    ui->setupUi(this);

    logic = nullptr;

    generateField();

    connect(ui->genButton, SIGNAL(clicked()), this, SLOT(generateField()));
}

CrossesAndZeros::~CrossesAndZeros()
{
    delete ui;
}

void CrossesAndZeros::printTurn(unsigned int value)
{
    ui->turnLabel->setText(QString::number(value));
}

void CrossesAndZeros::generateField()
{
    qDebug("===generateField begins");
    delete logic;
    const unsigned int newSize = ui->spinBox->value();
    for (unsigned int i = 0; i < currentSize; i++)
    {
        for (unsigned int j = 0; j < currentSize; j++)
        {
            delete ui->gridLayout->itemAtPosition(i, j)->widget();
        }
    }
    field.clear();
    for (unsigned int i = 0; i < newSize; i++)
    {
        for (unsigned int j = 0; j < newSize; j++)
        {
            QPushButton* button = new QPushButton;
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
            ui->gridLayout->addWidget(button, i, j);
            button->setText(" ");

            connect(button, SIGNAL(clicked()), this, SLOT(buttonClicked()));

            field[i * newSize + j] = button;
        }
    }

    currentSize = newSize;
    logic = new CrossesAndZerosLogic(this, currentSize);
    connect(this, SIGNAL(playersTurnW(unsigned int)), logic, SLOT(playersTurn(unsigned int)));
    connect(logic, SIGNAL(cellChanged(unsigned int, unsigned int, bool)),
            this, SLOT(setButton(unsigned int,unsigned int,bool)));
    connect(logic, SIGNAL(restart()), this, SLOT(generateField()));
    connect(logic, SIGNAL(turnMade(unsigned int)), this, SLOT(printTurn(unsigned int)));
    printTurn(0);
    qDebug("===generateField ends");
}

void CrossesAndZeros::setButton(unsigned int pos, unsigned int player, bool enable)
{
    qDebug("setButton begins");
    field[pos]->setEnabled(enable);
    field[pos]->setText(player == 1 ? "X" : "0");
    qDebug("setButton ends");
}

void CrossesAndZeros::buttonClicked()
{
    qDebug("buttonClicked begins");
    QPushButton* button = qobject_cast<QPushButton*>(sender());
    unsigned int buttonPos = 0;
    while (field[buttonPos] != button)
    {
        qDebug("bC!");
        buttonPos++;
    }
    setButton(buttonPos, 1, false);
    emit playersTurnW(buttonPos);
    qDebug("buttonClicked ends");
}
