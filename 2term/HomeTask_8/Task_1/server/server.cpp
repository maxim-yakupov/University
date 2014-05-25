#include <QtNetwork>
#include <QMessageBox>
#include "server.h"
#include "ui_server.h"

Server::Server(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Server),
    tcpServer(nullptr),
    tcpSocket(nullptr),
    networkSession(nullptr),
    blockSize(0)
{
    ui->setupUi(this);

    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)
    {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered)
        {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        ui->hostLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
    else
    {
        sessionOpened();
    }

    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpServer, SIGNAL(newConnection()), this, SLOT(receiveConnection()));
}

void Server::sessionOpened()
{
    // Save the used configuration
    if (networkSession)
    {
        QNetworkConfiguration config = networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
        {
            id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        }
        else
        {
            id = config.identifier();
        }

        QSettings settings(QSettings::UserScope, QLatin1String("QtProject"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    tcpServer = new QTcpServer(this);
    if (!tcpServer->listen())
    {
        QMessageBox::critical(this, tr("Fortune Server"),
                              tr("Unable to start the server: %1.")
                              .arg(tcpServer->errorString()));
        close();
        return;
    }

    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i)
    {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address())
        {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
    ui->hostLabel->setText(ipAddress);
    ui->portLabel->setText(QString::number(tcpServer->serverPort()));
}

void Server::receiveConnection()
{
    if (!tcpSocket)
    {
        disconnect(tcpSocket, SIGNAL(readyRead()), this, SLOT(incomeMessage()));
        delete tcpSocket;
    }
    tcpSocket = tcpServer->nextPendingConnection();
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(incomeMessage()));
}

void Server::incomeMessage()
{
    qDebug() << "incomeMessage";
    QDataStream in(tcpSocket);
    in.setVersion(QDataStream::Qt_4_0);

    if (blockSize == 0)
    {
        if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
        {
            return;
        }
        in >> blockSize;
    }

    if (tcpSocket->bytesAvailable() < blockSize)
    {
        return;
    }

    QString message;
    in >> message;

    if (ui->checkBox->isChecked())
    {
        ui->plainTextEdit->setPlainText(message);
    }
    else
    {
        ui->plainTextEdit->setPlainText(ui->plainTextEdit->toPlainText().append(message).append("\n"));
    }

    blockSize = 0;
    qDebug() << "incomeMessage: ends";
}

Server::~Server()
{
    delete ui;
}
