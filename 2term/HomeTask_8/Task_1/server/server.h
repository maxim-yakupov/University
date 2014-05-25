#pragma once

#include <QWidget>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QNetworkSession>

namespace Ui {
class Server;
}

/**
 * @brief The Server class
 */
class Server : public QWidget
{
    Q_OBJECT
public:
    explicit Server(QWidget *parent = 0);
    ~Server();
private slots:
    /**
     * @brief sessionOpened Sets host & port
     */
    void sessionOpened();
    /**
     * @brief receiveConnection Creates TCP-socket & connects it with incomeMessage()
     */
    void receiveConnection();
    /**
     * @brief incomeMessage Processes income data stream
     */
    void incomeMessage();
private:
    Ui::Server *ui;
    QTcpServer* tcpServer;
    QTcpSocket* tcpSocket;
    QNetworkSession* networkSession;
    quint16 blockSize;
};
