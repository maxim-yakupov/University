#pragma once

#include <QWidget>

namespace Ui {
class BashQuote;
}

class BashQuote : public QWidget
{
    Q_OBJECT

public:
    explicit BashQuote(QWidget *parent = 0, QString quoteId = "1", QString text = "");
    ~BashQuote();
    QString getId();
    QString getText();
    QString getRate();
signals:
    void votedPlus(QString);
    void votedMinus(QString);
    void votedBayan(QString);
public slots:
    void changeId(QString);
    void changeText(QString);
    void changeRate(QString);
private slots:
    void pressedPlus();
    void pressedMinus();
    void pressedBayan();
private:
    Ui::BashQuote *ui;

    QString quoteId;
};
