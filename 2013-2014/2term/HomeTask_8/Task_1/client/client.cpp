#include "client.h"
#include "ui_client.h"
#include <QMessageBox>

Client::Client(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    tcpSocket = new QTcpSocket(this);

    connect(ui->checkBox, SIGNAL(clicked()), this, SLOT(changeMode()));
    connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
    connect(ui->quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)),
            this, SLOT(displayError(QAbstractSocket::SocketError)));
    qDebug() << "QNetworkConfigurationManager";
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired)//!
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
        qDebug() << "networkSession";
        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        qDebug() << "networkSession: ends";
        qDebug() << "Opening network session";
        ui->textEdit->setText(tr("Opening network session."));
        networkSession->open();
        qDebug() << "Opening network session: ends";
    }
}

void Client::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The host was not found. Please check the "
                                    "host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The connection was refused by the peer. "
                                    "Make sure the fortune server is running, "
                                    "and check that the host name and port "
                                    "settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"),
                                 tr("The following error occurred: %1.")
                                 .arg(tcpSocket->errorString()));
    }
}

void Client::sessionOpened()
{
    qDebug() << "sessionOpened";
    // Save the used configuration
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

    ui->textEdit->setText(tr("This examples requires that you run the "
                            "Fortune Server example as well."));
    qDebug() << "sessionOpened: ends";
}

Client::~Client()
{
    delete ui;
}

void Client::changeMode()
{
    if (ui->checkBox->isChecked())
    {
        disconnect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
        connect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(sendMessage()));
        ui->sendButton->setEnabled(false);
    }
    else
    {
        disconnect(ui->textEdit, SIGNAL(textChanged()), this, SLOT(sendMessage()));
        connect(ui->sendButton, SIGNAL(clicked()), this, SLOT(sendMessage()));
        ui->sendButton->setEnabled(true);
    }
}

void Client::connectHost()
{
    qDebug() << "connectHost";
    blockSize = 0;
    tcpSocket->abort();
    tcpSocket->connectToHost(ui->hostLineEdit->text(),
                             ui->portLineEdit->text().toInt());
    qDebug() << "connectHost: ends";
}

void Client::sendMessage()
{
    qDebug() << "sendMessage";
    connectHost();
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    out << (quint16)0;
    out << ui->textEdit->toPlainText();
    out.device()->seek(0);
    out << (quint16)(block.size() - sizeof(quint16));

    tcpSocket->write(block);
    tcpSocket->disconnectFromHost();
    qDebug() << "sendMessage: ends";
}
