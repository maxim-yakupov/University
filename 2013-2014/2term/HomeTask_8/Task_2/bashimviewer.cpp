#include <QWebElement>
#include <QWebElementCollection>
#include <QWebPage>
#include <QWebFrame>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QByteArray>

#include <QDebug>
#include "bashimviewer.h"
#include "ui_bashimviewer.h"
#include "bashquote.h"
#include "ui_bashquote.h"

BashImViewer::BashImViewer(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::BashImViewer),
    manager(nullptr),
    view(nullptr),
    bQ(nullptr),
    maxId(0)
{
    ui->setupUi(this);

    manager = new QNetworkAccessManager(this);

    bQ = new BashQuote(this);
    ui->verticalLayout->addWidget(bQ);
    connect(bQ, SIGNAL(votedBayan(QString)), this, SLOT(voteBayan(QString)));
    connect(bQ, SIGNAL(votedMinus(QString)), this, SLOT(voteMinus(QString)));
    connect(bQ, SIGNAL(votedPlus(QString)), this, SLOT(votePlus(QString)));

    connect(this, SIGNAL(idUpdated(QString)), bQ, SLOT(changeId(QString)));
    connect(this, SIGNAL(textUpdated(QString)), bQ, SLOT(changeText(QString)));
    connect(this, SIGNAL(ratingUpdated(QString)), bQ, SLOT(changeRate(QString)));

    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->prevButton, SIGNAL(clicked()), this, SLOT(prev()));

    view = new QWebView();
    view->load(QUrl("http://bash.im/"));
    connect(view, SIGNAL(loadProgress(int)), ui->progressBar, SLOT(setValue(int)));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(firstRun(bool)));
}

BashImViewer::~BashImViewer()
{
    delete ui;
    delete manager;
    delete view;
    delete bQ;
}

void BashImViewer::next()
{
    unsigned int id = bQ->getId().toUInt() - 1;
    if (id <= maxId)
    {
        loadQuote(QString::number(id));
    }
    else
    {
        emit textUpdated("invalid id");
    }
}

void BashImViewer::prev()
{
    unsigned int id = bQ->getId().toUInt() + 1;
    if (id <= maxId)
    {
        loadQuote(QString::number(id));
    }
    else
    {
        emit textUpdated("invalid id");
    }
}

void BashImViewer::loadQuote(QString id)
{
    emit idUpdated(id);
    emit textUpdated("loading...");
    emit ratingUpdated("loading...");
    QString url;
    url.append("http://bash.im/quote/");
    url.append(id);
    view->load(QUrl(url));
    ui->progressBar->setHidden(false);
    connect(view, SIGNAL(loadProgress(int)), ui->progressBar, SLOT(setValue(int)));
    connect(view, SIGNAL(loadFinished(bool)), this, SLOT(emitSignalsToUpdate(bool)));
}

void BashImViewer::emitSignalsToUpdate(bool ok)
{
    Q_UNUSED(ok);
    ui->progressBar->setHidden(true);
    disconnect(view, SIGNAL(loadFinished(bool)), this, SLOT(emitSignalsToUpdate(bool)));
    emit textUpdated(view->page()->mainFrame()->findFirstElement("div[class=text]").toPlainText());
    emit ratingUpdated(view->page()->mainFrame()->findFirstElement("span[class=rating]").toPlainText());
}

void BashImViewer::votePlus(QString quoteId)
{
    qDebug() << "votePlus";
//    QString urlPart;
//    urlPart.append("http://bash.im/quote/");
//    urlPart.append(quoteId);
//    urlPart.append("/rulez");

//    QUrl url(urlPart);

//    QByteArray requestData = "quote=";
//    requestData.append(quoteId);
//    requestData.append("&act=rulez");

//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
//    request.setHeader(QNetworkRequest::ContentLengthHeader,
//        QByteArray::number(requestData.length()));

//    QNetworkReply* reply = manager->post(request, requestData);
//    delete reply;

//    QWebElement rate = view->page()->mainFrame()->findFirstElement("span[id=v" + quoteId + "]");
//    emit ratingUpdated(rate.toPlainText());
}

void BashImViewer::voteMinus(QString quoteId)
{
    qDebug() << "voteMinus";
//    QString urlPart;
//    urlPart.append("http://bash.im/quote/");
//    urlPart.append(quoteId);
//    urlPart.append("/sux");
//    QUrl url(urlPart);
//    QByteArray requestData = "quote=";
//    requestData.append(quoteId);
//    requestData.append("&act=sux");
//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
//    request.setHeader(QNetworkRequest::ContentLengthHeader,
//        QByteArray::number(requestData.length()));
//    QNetworkReply *reply = manager->post(request, requestData);
//    delete reply;
//    QWebElement rate = view->page()->mainFrame()->findFirstElement("span[id=v" + quoteId + "]");
//    emit ratingUpdated(rate.toPlainText());
}

void BashImViewer::voteBayan(QString quoteId)
{
    qDebug() << "voteBayan";
//    QString urlPart;
//    urlPart.append("http://bash.im/quote/");
//    urlPart.append(quoteId);
//    urlPart.append("/bayan");
//    QUrl url(urlPart);
//    QByteArray requestData = "quote=";
//    requestData.append(quoteId);
//    requestData.append("&act=bayan");
//    QNetworkRequest request(url);
//    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/html");
//    request.setHeader(QNetworkRequest::ContentLengthHeader,
//        QByteArray::number(requestData.length()));
//    QNetworkReply *reply = manager->post(request, requestData);
//    delete reply;
//    QWebElement rate = view->page()->mainFrame()->findFirstElement("span[id=v" + quoteId + "]");
//    emit ratingUpdated(rate.toPlainText());
}

void BashImViewer::firstRun(bool ok)
{
    Q_UNUSED(ok);
    ui->progressBar->setHidden(true);
    disconnect(view, SIGNAL(loadFinished(bool)), this, SLOT(firstRun(bool)));
    maxId = view->page()->mainFrame()->findFirstElement("a[class=id]").toPlainText().remove(0, 1).toUInt();
    loadQuote(QString::number(maxId));
}
