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

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

 //---------------- [qt connection]---------------
 /*   net::io_context ioc;
    ioc.run();

    std::unique_ptr<Client> client(new Client);

    auto const port = 8000;
    // auto const host = "25.40.253.246";
    auto const host = "127.0.0.1";
    auto const target = "/test.txt";

    // QByteArray name;
    // name.append("Sergey");
    // client->post(host, port, target, name);

    client->getData(host, port, target);*/

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
    auto const port = "8000";
    //auto const target = "index.html";
    //auto const version = "1.1";
    //auto const host = "scooterlabs.com";
    //auto const target = "/echo?input=test";
    //auto const host = "192.168.1.110";
    //auto const host = "192.168.1.26";
    //auto const host = "25.40.253.246";
    auto const host = "127.0.0.1";
    auto const target = "/1108_syms_pass.txt";
    auto const version = 11;

    // The io_context is required for all I/O
    net::io_context ioc;
    std::set<std::shared_ptr<session>> sessions;

    // Launch the asynchronous operation
    std::cout << "CLIENT [" << 1 << "]\nConnecting to " << host << ':' << port << "\nTrying to GET " << target << std::endl;
    /*client1*/  std::make_shared<session>(ioc)->run(host, port, target, version);
    for (int i = 0; i < 0; ++i) {
        sleep(DELAY);
        std::cout << "CLIENT [" << i + 2 << "]\nConnecting to " << host << ':' << port << "\nTrying to GET " << target << std::endl;
        sessions.insert(std::make_shared<session>(ioc));
    }
    // Run the I/O service. The call will return when
    // the get operation is complete.
    ioc.run();


// -------------------------------------[ end boost example]---------------------------------

    std::shared_ptr<Database> db = std::make_shared<Database>();
    MainWindow w(db);
    w.show();

    system("pause");
    return a.exec();
    // return EXIT_SUCCESS;
}
