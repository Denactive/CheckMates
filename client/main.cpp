/*#include "include/windows/mainwindow.h"
#include "include/graphics.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <QTcpServer>

#include <memory>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include "include/serverconnection.h"
//#include "include/wsclient.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    QApplication a(argc, argv);

    // runGame();

    // testWSClient();

    std::shared_ptr<Database> db = std::make_shared<Database>();

//    SessionSingleton::instance();
//    auto connection = SessionSingleton::instance().get();//->run(host, port);
//    connection->run(host, port);

//    std::thread t([](){
//        SessionSingleton::instance().get_ioc().run();
//    });
    t.detach();
    //SessionSingleton::instance().get_ioc().run();

    MainWindow w(db);
    w.show();

    system("pause");
    return a.exec();
    // return EXIT_SUCCESS;
}*/

#include "include/global.h"
#include "include/database.h"
#include "include/graphics.h"
#include <QApplication>

#include "include/echoclient.h"
#include "include/windows/mainwindow.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    msg_Singleton::instance();
    queryReceive::instance();
    QApplication a(argc, argv);

    /*QCommandLineParser parser;
    parser.setApplicationDescription("QtWebSockets example: echoclient");
    parser.addHelpOption();

    QCommandLineOption dbgOption(QStringList() << "d" << "debug",
            QCoreApplication::translate("main", "Debug output [default: off]."));
    parser.addOption(dbgOption);
    parser.process(a);*/
    // bool debug = true; // parser.isSet(dbgOption);

    std::shared_ptr<Database> db = std::make_shared<Database>();
    auto const h_port = 8000;
    std::shared_ptr<std::string> h_host = std::make_shared<std::string>("25.34.102.253"); // "127.0.0.1");

    std::shared_ptr<EchoClient> webSocket = std::make_shared<EchoClient>(QUrl(QStringLiteral("ws://25.34.102.253:1234")), DEBUGSOCKET, db); //25.34.102.253:1234")), DEBUGSOCKET);
    std::shared_ptr<Client> httpClient = std::make_shared<Client>(h_host, h_port, db);
    GlobalNet *globalNet = new GlobalNet();
    globalNet->httpClient = httpClient;
    globalNet->webSocket = webSocket;

    globalNet->webSocket->doReceive();
    globalNet->webSocket->doSend("msg start from client");

    MainWindow w(db, globalNet);
    w.show();

    // QObject::connect(&client, &EchoClient::closed, &a, &QApplication::quit);
    return a.exec();
}
