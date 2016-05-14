#pragma once

#include <QWidget>
#include <QtNetwork>

namespace Ui {
class Client;
}

/**
 * @brief The Client class
 */
class Client : public QWidget
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
private slots:
    /**
     * @brief changeMode Changes 'mirror mode'
     * @detailed 'Mirror mode': on - what we type in client is what we get in server
     *                          off - ordinary sending of messages(sends when click on 'Send' button)
     */
    void changeMode();
    /**
     * @brief sendMessage Connects to server with connectHost() & send message to server
     */
    void sendMessage();
    /**
     * @brief connectHost Connects to server
     */
    void connectHost();
    /**
     * @brief displayError Pop-up error
     * @param socketError Error type
     */
    void displayError(QAbstractSocket::SocketError socketError);
    /**
     * @brief sessionOpened Sets host & port of receiver
     */
    void sessionOpened();
private:
    Ui::Client *ui;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;

    QNetworkSession *networkSession;
};
