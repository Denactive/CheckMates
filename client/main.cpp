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
    QApplication a(argc, argv);

 //---------------- [qt connection]---------------
    std::unique_ptr<Client> client(new Client);

    auto const port = 8001;
    // auto const host = "25.40.253.246";
    // auto const host = "127.0.0.1";
    auto const host = "25.34.102.253";
    auto const target = "/test.txt";

    // QByteArray name;
    // name.append("Sergey");
    // client->post(host, port, target, name);

    client->getData(host, port, target);

// -------------------------------------- [boost example]--------------------------------------
    setlocale(LC_ALL, "rus");
    // Check command line arguments.
    /*if (argc != 4 && argc != 5)
    {
        std::cerr <<
            "Usage: http-client-async <host> <port> <target> [<HTTP version: 1.0 or 1.1(default)>]\n" <<
            "Example:\n" <<
            "    http-client-async www.example.com 80 /\n" <<
            "    http-client-async www.example.com 80 / 1.0\n";
        return EXIT_FAILURE;
    }
    auto const host = argv[1];
    auto const port = argv[2];
    auto const target = argv[3];
    int version = argc == 5 && !std::strcmp("1.0", argv[4]) ? 10 : 11;
    */
    // auto const host = "93.184.216.34";
    auto const port2 = "8001";
    //auto const target = "index.html";
    //auto const version = "1.1";
    //auto const host = "scooterlabs.com";
    //auto const target = "/echo?input=test";
    //auto const host = "192.168.1.110";
    //auto const host = "192.168.1.26";
    //auto const host2 = "25.40.253.246";
    auto const host2 = "25.34.102.253";
    //auto const host2 = "127.0.0.1";
    // auto const target2 = "/1108_syms_pass.txt";
    // auto const version = 11;
    auto const text = "it is a test";

    // The io_context is required for all I/O
    net::io_context ioc;


    // Launch the asynchronous operation
    std::make_shared<wssession>(ioc)->run(host2, port2, text);

    // Run the I/O service. The call will return when
    // the socket is closed.
    ioc.run();


// -------------------------------------[ end boost example]---------------------------------

    std::shared_ptr<Database> db = std::make_shared<Database>();
    MainWindow w(db);
    w.show();

    system("pause");
    return a.exec();
    // return EXIT_SUCCESS;
}
