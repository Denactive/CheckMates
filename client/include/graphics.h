#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <iostream>
#include <QObject>
#include <QDebug>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <QAuthenticator>
#include <QNetworkProxy>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>

// #include <QtWebSockets/QWebSocket>

#include "include/community.h"
#include "include/chessboard.h"
#include "include/figures.h"
#include "include/windows/mainwindow.h"
#include "include/database.h"
#include <unistd.h>

#include <../boost/beast/http.hpp>
#include <../boost/asio/strand.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

// QNetworkAccessManager - инкапсулирует HTTP протокол, включает SSL

class Client : public QObject {
    Q_OBJECT
public:
    Client(QObject *parent = nullptr);
    QUrl setUrl(char const* host, int port, char const* target);

signals:
    void onReady();

public slots:
    void getData(char const* host, int port, char const* target);
    void post(char const* host, int port, char const* target, QByteArray data);

private slots:
    void readyRead();

    void parseFromJSON(std::shared_ptr<QFile> file);
    void parseToJSON(std::shared_ptr<QFile> file);

    void authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator);
    void encrypted(QNetworkReply *reply);
    void finished(QNetworkReply *reply);
    void networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible);
    void preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator);
    void proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator);
    void sslErrors(QNetworkReply *reply, const QList<QSslError> &errors);

private:
    QNetworkAccessManager manager;
};

/*
class EchoClient : public QObject {
    Q_OBJECT
public:
    EchoClient(const QUrl &url, bool debug, QObject *parent);

signals:
    void onConnected();
    void closed();
    void onTextMessageReceived(QString message);
private:
    QUrl m_url;
    bool m_debug;
    QWebSocket m_webSocket;
};*/

#endif // GRAPHICS_H
