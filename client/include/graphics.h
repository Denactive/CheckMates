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

#include "include/community.h"
#include "include/chessboard.h"
#include "include/figures.h"
#include "include/windows/mainwindow.h"
#include "include/database.h"

// QNetworkAccessManager - инкапсулирует HTTP протокол, включает SSL

class Client : public QObject {
    Q_OBJECT
public:
    Client(QObject *parent = nullptr);

signals:

public slots:
    void getData(char const* host, int port, char const* target);
    void post(QString location, QByteArray data);

private slots:
    void readyRead();
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

#endif // GRAPHICS_H
