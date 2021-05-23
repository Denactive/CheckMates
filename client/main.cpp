#include "include/windows/mainwindow.h"
#include "include/graphics.h"

#include <QApplication>
#include <QWidget>
#include <QGridLayout>
#include <boost/asio/strand.hpp>
#include <boost/beast/http.hpp>
#include <memory>
#include <QTcpServer>

namespace net = boost::asio;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    net::io_context ioc;
    ioc.run();

    std::unique_ptr<Client> client(new Client);

    auto const port = 8000;
    // auto const host = "25.40.253.246";
    auto const host = "127.0.0.1";
    auto const target = "/test.txt";

    QByteArray name;
    name.append("Sergey");
    client->post(host, port, target, name);

    client->getData(host, port, target);

    std::shared_ptr<Database> db = std::make_shared<Database>();
    MainWindow w(db);
    w.show();

    return a.exec();
}
