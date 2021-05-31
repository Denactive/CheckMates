#ifndef GRAPHICS_H
#define GRAPHICS_H

#define HTTPDEBUG 0

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

#include "include/community.h"
#include "include/figures.h"
#include "include/database.h"
#include "include/echoclient.h"
#include <unistd.h>
#include <string>

#include <../boost/beast/http.hpp>
#include <../boost/asio/strand.hpp>

namespace beast = boost::beast;
namespace http = beast::http;
namespace net = boost::asio;

// QNetworkAccessManager - инкапсулирует HTTP протокол, включает SSL
class MyCookieJar : public QNetworkCookieJar
{
    public:
        QList<QNetworkCookie> getAllCookies() { return allCookies(); }
};

class Client : public QObject {
    Q_OBJECT
public:
    Client(QObject *parent = nullptr);
    QUrl setUrl(char const* host, int port, char const* target);
    void download(QString);
    void _download(QUrl);
    std::shared_ptr<std::string> getToken() { return token_; }
    QNetworkAccessManager & getManager() { return manager; }

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
    MyCookieJar *cookieJar;
    QList<QNetworkCookie> cookiesList;
    std::shared_ptr<std::string> token_;
};

typedef struct {
    std::shared_ptr<EchoClient> webSocket;
    std::shared_ptr<Client> httpClient;
} GlobalNet;

#endif // GRAPHICS_H
