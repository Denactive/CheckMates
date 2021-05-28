#include "include/windows/mainwindow.h"
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
#include "include/wsclient.h"

int main(int argc, char *argv[])
{
    setlocale(LC_ALL, "rus");
    QApplication a(argc, argv);

    runGame();

 //---------------- [qt connection]---------------
    std::unique_ptr<Client> client(new Client);

    auto const h_port = 8000;
    // auto const host = "25.40.253.246";
    auto const h_host = "127.0.0.1";
    // auto const host = "25.34.102.253";
    auto const h_target = "/test_cookie.php";

    QByteArray name;
    name.append("Sergey");
    client->post(h_host, h_port, h_target, name);
    client->getData(h_host, h_port, h_target);
    client->_download(client->setUrl(h_host, h_port, h_target));
 //-----------------------[end at connection]---------------

    std::shared_ptr<Database> db = std::make_shared<Database>();

    /*SessionSingleton::instance();
    auto connection = SessionSingleton::instance().get();//->run(host, port);
    connection->run(host, port);*/

    /*std::thread t([](){
        SessionSingleton::instance().get_ioc().run();
    });
    t.detach();*/
    //SessionSingleton::instance().get_ioc().run();

    MainWindow w(db);
    w.show();

    system("pause");
    return a.exec();
    // return EXIT_SUCCESS;
}
