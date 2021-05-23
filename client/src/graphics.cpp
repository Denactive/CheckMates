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

    QNetworkReply *reply = manager.get(QNetworkRequest(setUrl(host, port, target)));
    connect(reply, &QNetworkReply::readyRead, this, &Client::readyRead);
}

void Client::post(char const* host, int port, char const* target, QByteArray data)
{
    qInfo() << "Post data to server";
    QNetworkRequest request = QNetworkRequest(setUrl(host, port, target));
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
        // qInfo() << reply->readAll();
        std::shared_ptr<QFile> file = std::make_shared<QFile>("../../server/storage/getdata.txt");
        if (file->open(QFile::WriteOnly)) {
            file->write(reply->readAll());
            file->close();
        } else {
            qDebug() << "file not open";
        }

        // просто тест - после того, как записали в файл считываем с него и переводим с json формата
        parseFromJSON(file);
        parseToJSON(file);
    }

    qDebug() << "Data is get";
    emit onReady();
}

void Client::parseFromJSON(std::shared_ptr<QFile> file)
{
    // заглушка
    file->open(QFile::ReadOnly);
    QByteArray data = file->readAll();
    QJsonDocument document;
    document = document.fromJson(data);
    QString value = document.object()["name"].toString();
    qDebug() << "value: " << value;
}

void Client::parseToJSON(std::shared_ptr<QFile> file) {
    file->open(QFile::ReadOnly);
    QJsonObject obj = QJsonDocument::fromJson(file->readAll()).object();
    obj["name"] = "Anton";
    file->close();
    file->open(QFile::WriteOnly);
    file->write(QJsonDocument(obj).toJson());
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

QUrl Client::setUrl(char const* host, int port, char const* target)
{
    QUrl url;
    url.setHost(host);
    url.setPort(port);
    url.setScheme("http");
    url.setPath(target);
    qDebug() << url;

    return url;
}
