#ifndef ECHOCLIENT_H
#define ECHOCLIENT_H

#define DEBUGSOCKET 1

#include <QDebug>
#include <QtCore/QObject>
#include <QtWebSockets/QWebSocket>
#include <QtCore/QCoreApplication>
#include <QtCore/QCommandLineParser>
#include <QtCore/QCommandLineOption>
#include <memory>
#include "include/database.h"
#include "include/global.h"

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false, std::shared_ptr<Database> db = std::make_shared<Database>(), QObject *parent = nullptr);
    void doSend(std::string msg);
    void doReceive();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
    std::shared_ptr<Database> db;
};

#endif // ECHOCLIENT_H
