
#include "include/echoclient.h"
#include <QtCore/QDebug>

QT_USE_NAMESPACE

//! [constructor]
EchoClient::EchoClient(const QUrl &url, bool debug, std::shared_ptr<Database> db, QObject *parent) :
    QObject(parent),
    m_url(url),
    m_debug(debug),
    db(db)
{
    if (m_debug)
        qDebug() << "WebSocket server:" << url;
    connect(&m_webSocket, &QWebSocket::connected, this, &EchoClient::onConnected);
    connect(&m_webSocket, &QWebSocket::disconnected, this, &EchoClient::closed);
    m_webSocket.open(QUrl(url));
    qDebug() << "end of open";
}
//! [constructor]

//! [onConnected]
void EchoClient::onConnected()
{
    qDebug() << "connected";
    if (m_debug)
        qDebug() << "WebSocket connected";    
}
//! [onConnected]

void EchoClient::doReceive()
{
    connect(&m_webSocket, &QWebSocket::textMessageReceived,
            this, &EchoClient::onTextMessageReceived);
}

void EchoClient::doSend(std::string msg)
{
    m_webSocket.sendTextMessage(QString::fromUtf8(msg.c_str()));
}

//! [onTextMessageReceived]
void EchoClient::onTextMessageReceived(QString message)
{
    if (m_debug)
        qDebug() << "Message received:" << message;
    auto tmpReceive = true;
    queryReceive::instance().set(tmpReceive);
}
//! [onTextMessageReceived]
