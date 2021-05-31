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

class EchoClient : public QObject
{
    Q_OBJECT
public:
    explicit EchoClient(const QUrl &url, bool debug = false, QObject *parent = nullptr);
    void doSend(std::string msg);
    void doReceive();

Q_SIGNALS:
    void closed();

private Q_SLOTS:
    void onConnected();
    void onTextMessageReceived(QString message);
//    void close(QWebSocketProtocol::CloseCode protocol, QString const& text) {  }
//    void textMessageReceived(QString const& text) { Q_UNUSED(text); }

//    void disconnected();
//    void connected();
//    void QWebSocket(QString const&, QWebSocketProtocol::Version, QObject*)»
//    void sendTextMessage(QString const&);
//    void open(QUrl const&);
//   \ void ~QWebSocket();

private:
    QWebSocket m_webSocket;
    QUrl m_url;
    bool m_debug;
};

#endif // ECHOCLIENT_H
