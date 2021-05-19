#include "include/graphics.h"

Client::Client(QObject *parent) :QObject(parent)
{
    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &Client::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &Client::encrypted);
    connect(&manager, &QNetworkAccessManager::networkAccessibleChanged, this, &Client::networkAccessibleChanged);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Client::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &Client::proxyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &Client::sslErrors);
}

void Client::getData(char const* host, int port, char const* target)
{
    qInfo() << "Get data from server";
    QUrl url;
    url.setHost(host);
    url.setPort(port);
    url.setScheme("http");
    url.setPath(target);
    qDebug() << url;

    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, &QNetworkReply::readyRead, this, &Client::readyRead);
}

void Client::post(QString location, QByteArray data)
{
    qInfo() << "Post data to server";
    QNetworkRequest request = QNetworkRequest(QUrl(location));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");

    QNetworkReply *reply = manager.post(request, data);
    connect(reply, &QNetworkReply::readyRead, this, &Client::readyRead);
}

void Client::readyRead()
{
    qInfo() << "ready to read";

    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error()) {
        qDebug() << "Reply error";
    } else {
        //qInfo() << reply->readAll();
        QFile *file = new QFile("../../storage/getdata.txt");
        if (file->open(QFile::WriteOnly)) {
            file->write(reply->readAll());
            file->close();
        } else {
            qDebug() << "file not open";
        }
    }

    qDebug() << "Data is get";
    emit onReady();
}

void Client::authenticationRequired(QNetworkReply *reply, QAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);

    qInfo() << "authenticationRequired";

}

void Client::encrypted(QNetworkReply *reply)
{
    Q_UNUSED(reply);

    qInfo() << "encrypted";
}

void Client::finished(QNetworkReply *reply)
{
    Q_UNUSED(reply);

    qInfo() << "finished";
}

void Client::networkAccessibleChanged(QNetworkAccessManager::NetworkAccessibility accessible)
{
    Q_UNUSED(accessible);

    qInfo() << "networkAccessibleChanged";
}

void Client::preSharedKeyAuthenticationRequired(QNetworkReply *reply, QSslPreSharedKeyAuthenticator *authenticator)
{
    Q_UNUSED(reply);
    Q_UNUSED(authenticator);

    qInfo() << "preSharedKeyAuthenticationRequired";
}

void Client::proxyAuthenticationRequired(const QNetworkProxy &proxy, QAuthenticator *authenticator)
{
    Q_UNUSED(proxy);
    Q_UNUSED(authenticator);

    qInfo() << "proxyAuthenticationRequired";
}

void Client::sslErrors(QNetworkReply *reply, const QList<QSslError> &errors)
{
    Q_UNUSED(reply);
    Q_UNUSED(errors);

    qInfo() << "sslErrors";
}
