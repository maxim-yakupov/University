#pragma once

#include <QWidget>
#include <QWebView>
#include "bashquote.h"

namespace Ui {
class BashImViewer;
}

class BashImViewer : public QWidget
{
    Q_OBJECT

public:
    explicit BashImViewer(QWidget *parent = 0);
    ~BashImViewer();
signals:
    void idUpdated(QString);
    void textUpdated(QString);
    void ratingUpdated(QString);
public slots:
    void votePlus(QString);
    void voteMinus(QString);
    void voteBayan(QString);
private slots:
    void next();
    void prev();
    void loadQuote(QString id);
    void emitSignalsToUpdate(bool ok);
    void firstRun(bool ok);
private:
    Ui::BashImViewer *ui;
    QNetworkAccessManager* manager;
    QWebView* view;
    BashQuote* bQ;
    unsigned int maxId;
};
