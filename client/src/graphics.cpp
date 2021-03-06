#include "include/graphics.h"

Client::Client(std::shared_ptr<std::string> host, int port, std::shared_ptr<Database> db, std::shared_ptr<std::string> target, QObject *parent)
    : host(host), port(port), db(db)
{
    token_ = std::make_shared<std::string>();
    connect(&manager, &QNetworkAccessManager::authenticationRequired, this, &Client::authenticationRequired);
    connect(&manager, &QNetworkAccessManager::encrypted, this, &Client::encrypted);
    connect(&manager, &QNetworkAccessManager::networkAccessibleChanged, this, &Client::networkAccessibleChanged);
    connect(&manager, &QNetworkAccessManager::preSharedKeyAuthenticationRequired, this, &Client::preSharedKeyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::proxyAuthenticationRequired, this, &Client::proxyAuthenticationRequired);
    connect(&manager, &QNetworkAccessManager::sslErrors, this, &Client::sslErrors);

    connect(&manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finished(QNetworkReply*)));

    cookieJar = new MyCookieJar();
    manager.setCookieJar(cookieJar);
}

void Client::getData(std::shared_ptr<std::string> target, char status)
{
    qInfo() << "Get data from server";

    QNetworkReply *reply = manager.get(QNetworkRequest(QUrl(setUrl(host->c_str(), port, target->c_str()))));

    QString name;
    if (status != '\0') {
        switch(status) {
            case 'l' :
                connect(reply, &QNetworkReply::readyRead, this, &Client::readyRead);
                name = QString::fromLocal8Bit(target->substr(10).c_str());
                setRegisterUserSettings(name);
                break;
            case 's':
                setStartGameInfo(reply);
                // connect(reply, &QNetworkReply::readyRead, this, &Client::setStartGameInfo);
                break;
            default:
                break;
        }
    }
}

void Client::post(char const* host, int port, char const* target, QByteArray data)
{
    qInfo() << "Post data to server";
    QNetworkRequest request = QNetworkRequest(setUrl(host, port, target));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "text/plain");
    request.setRawHeader(QByteArray("Cookie"), QByteArray("TS015810ea_76=088fa"));

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
            QByteArray rp = reply->readAll();
            // QString::fromUtf8(data);
            QList<QByteArray> headerList = reply->rawHeaderList();
            for (auto & header : headerList) {
                if (header == "Set-Cookie") {
                    QString cookie = reply->rawHeader(header);
                    if (HTTPDEBUG)  qDebug() << "Cookie: " << header + ": " + cookie;
                    std::string msg = cookie.toStdString();
                    auto beg = msg.find("token=") + 6;
                    //auto end = msg.substr(beg).find('\"');
//                    token_ = std::make_shared<std::string>(msg.substr(beg, end));
//                    global_token = msg.substr(beg, end);
                    auto tmp = msg.substr(beg);
                    msg_Singleton::instance().set(tmp);
                    // qDebug() << "token: " << QString::fromLocal8Bit(token_->c_str());
                }
            }

            qDebug() << "reply: " << rp;
            file->write(rp);
            file->close();
        } else {
            qDebug() << "file not open";
        }

        // ???????????? ???????? - ?????????? ????????, ?????? ???????????????? ?? ???????? ?????????????????? ?? ???????? ?? ?????????????????? ?? json ??????????????
        // parseFromJSON(file);
        // parseToJSON(file);
    }

    if (HTTPDEBUG)  qDebug() << "Data is get";
    emit onReady();
    // emit MainWindow::onSaveToken();
}

void Client::setStartGameInfo(QNetworkReply *reply) {
    qDebug() << "setStartGameInfo";
    // QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (reply->error()) {
        qDebug() << "Reply error";
    } else {
        QByteArray query2 = reply->readAll();
        qDebug() << "get " << query2;
        //QByteArray query = "";

        std::shared_ptr<QFile> file = std::make_shared<QFile>("../../server/storage/test.json");
        file->open(QFile::ReadOnly);
        QByteArray query = file->readAll();
        qDebug() << "parse " << query;


        QJsonDocument document;
        document = document.fromJson(query);
        int uid = document.object()["uid"].toString().toInt();
        std::shared_ptr<QString> gameToken = std::make_shared<QString>(document.object()["game_token"].toString());
        QString side = document.object()["side"].toString();

        QJsonObject opponent = document.object()["opponent"].toObject();
        std::shared_ptr<QString> opponentName = std::make_shared<QString>(opponent["name"].toString());
        int opponentRating = opponent["rating"].toString().toInt();
        std::shared_ptr<QString> avatarUrl = std::make_shared<QString>(opponent["avatar"].toString());
        std::shared_ptr<QPixmap> opponentAvatar = std::make_shared<QPixmap>(50, 50);
        opponentAvatar->load(("../img/" + avatarUrl->toStdString()).c_str());

        qDebug() << "game token " << *(gameToken) << "uid " << uid << "opponent name "<< *(opponentName) << "side" << side
            << "opponent rating: " << opponentRating << "url:" << *(avatarUrl) << "opponent avatar" << *(opponentAvatar);
        db->setStartGameInfo(gameToken, uid, opponentName, opponentRating, opponentAvatar, side == "white" ? true : false);
    }
}

void Client::parseFromJSON(std::shared_ptr<QFile> file)
{
    // ????????????????
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
    qInfo() << "finished";
    if (HTTPDEBUG) qDebug() << reply->readAll();
    if (HTTPDEBUG) qDebug() << "getAllCookies: " << cookieJar->getAllCookies();
    auto tmp = true;
    queryReceive::instance().set(tmp);
    QList<QByteArray> headerList = reply->rawHeaderList();
        foreach(QByteArray head, headerList) {
            // qDebug() << head << ":" << reply->rawHeader(head);
        }
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
    std::shared_ptr<QUrl> url = std::make_shared<QUrl>();
    url->setHost(host);
    url->setPort(port);
    url->setScheme("http");
    url->setPath(target);
    qDebug() << *(url);

    return *(url);
}

void Client::download(std::shared_ptr<std::string> target)
{
    _download(setUrl(host->c_str(), port, target->c_str()));
}

void Client::_download(QUrl url)
{
    qDebug() << "downland from url";
    //enters event loop, simulate blocking io
    QEventLoop q;
    QTimer t;
    t.setSingleShot(true);
    connect(&t, SIGNAL(timeout()), &q, SLOT(quit()));

    QNetworkReply *reply = manager.get(QNetworkRequest(url));
    connect(reply, SIGNAL(finished()), &q, SLOT(quit()));

    t.start(5000);
    q.exec();

    if (t.isActive()) {
        t.stop();
        QByteArray response = reply->readAll();
        if (HTTPDEBUG)  qDebug() << response;

        QVariant redirectionTarget = reply->attribute(QNetworkRequest::RedirectionTargetAttribute);
        if (reply->error()) {
            if (HTTPDEBUG)  qDebug()<< "Download failed" <<  reply->errorString();
        } else if (!redirectionTarget.isNull()) {
            QUrl newUrl = url.resolved(redirectionTarget.toUrl());
            if (HTTPDEBUG)  qDebug()<< "Redirect to" <<  newUrl.toString();
            url = newUrl;
            // reply->deleteLater();
            _download(url);
        } else {
            if (HTTPDEBUG) qDebug() << "Finish! ";
        }

        reply->deleteLater();

    } else {
        if (HTTPDEBUG)  qDebug() << "Timeout";
    }

    cookiesList = cookieJar->getAllCookies();
    if (HTTPDEBUG)  qDebug() << "getAllCookies: " << cookiesList;
}

void Client::setRegisterUserSettings(QString name)
{
    QPixmap truePixmap(50, 50);
    truePixmap.load(("../img/users/" + name.toStdString() + ".png").c_str());
    truePixmap = truePixmap.scaled(QSize(50, 50));

    db->addUser(1, name, "svetlanlka", "1234", truePixmap, 0);
}
