#include <QWebElement>
#include <QWebElementCollection>
#include <QWebPage>
#include <QWebFrame>
#include "bashquote.h"
#include "ui_bashquote.h"

BashQuote::BashQuote(QWidget *parent, QString quoteId, QString text) :
    QWidget(parent),
    ui(new Ui::BashQuote),
    quoteId(quoteId)
{
    ui->setupUi(this);
    changeText(text);
    connect(ui->bayanButton, SIGNAL(clicked()), this, SLOT(pressedBayan()));
    connect(ui->pushButtonMinus, SIGNAL(clicked()), this, SLOT(pressedMinus()));
    connect(ui->pushButtonPlus, SIGNAL(clicked()), this, SLOT(pressedPlus()));
}

BashQuote::~BashQuote()
{
    delete ui;
}

QString BashQuote::getId()
{
    return quoteId;
}

QString BashQuote::getText()
{
    return ui->label_quote->toPlainText();
}

QString BashQuote::getRate()
{
    return ui->label_votes->text();
}

void BashQuote::changeId(QString id)
{
    quoteId = id;
}

void BashQuote::changeText(QString text)
{
    ui->label_quote->setPlainText(text);
}

void BashQuote::pressedPlus()
{
    emit votedPlus(quoteId);
}

void BashQuote::pressedMinus()
{
    emit votedMinus(quoteId);
}

void BashQuote::pressedBayan()
{
    emit votedBayan(quoteId);
}

void BashQuote::changeRate(QString rate)
{
    ui->label_votes->setText(rate);
}
