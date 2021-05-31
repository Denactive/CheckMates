#ifndef GRAPHICS_H
#define GRAPHICS_H

#define HTTPDEBUG 0

#include "global.h"
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

#include <QtNetwork>
#include <QtCore>

// #include <QtWebSockets/QWebSocket>

// #include "include/community.h"
// #include "include/figures.h"
// #include "include/database.h"
#include "include/echoclient.h"
// #include "include/windows/mainwindow.h"
#include <unistd.h>
#include <string>
#include <functional>

#include <../boost/beast/http.hpp>
#include <../boost/asio/strand.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

static void init(){}

typedef std::function<void()> fp;

// QNetworkAccessManager - инкапсулирует HTTP протокол, включает SSL
class MyCookieJar : public QNetworkCookieJar
{
    public:
        QList<QNetworkCookie> getAllCookies() { return allCookies(); }
};

class Client : public QObject {
    Q_OBJECT
public:
    Client(std::shared_ptr<std::string> host = std::make_shared<std::string>("127.0.0.1"), int port = 8000,
           std::shared_ptr<std::string> target = std::make_shared<std::string>("/"), QObject *parent = nullptr);
    QUrl setUrl(char const* host, int port, char const* target);
    void download(std::shared_ptr<std::string> target);
    void _download(QUrl);
    std::shared_ptr<std::string> getToken() { return token_; }
    QNetworkAccessManager & getManager() { return manager; }

signals:
    void onReady();

public slots:
    void getData(std::shared_ptr<std::string> target, const std::function <void ()> &signal = nullptr);
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
    MyCookieJar *cookieJar;
    QList<QNetworkCookie> cookiesList;
    std::shared_ptr<std::string> token_;

    std::shared_ptr<std::string> host;
    int port;
    std::shared_ptr<std::string> target;

    fp _signal = init;
};

typedef struct {
    std::shared_ptr<EchoClient> webSocket;
    std::shared_ptr<Client> httpClient;
} GlobalNet;

#endif // GRAPHICS_H
