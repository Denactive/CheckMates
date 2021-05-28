#include "include/wsclient.h"

void wsfail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}
// Start the asynchronous operation
void
    wssession::run(
        char const* host,
        char const* port)
{
    if (WBASIC_DEBUG) qDebug() << "run\n";
    // Save these for later
    host_ = host;
    need_close = false;

    // Look up the domain name
    resolver_.async_resolve(
        host,
        port,
        beast::bind_front_handler(
            &wssession::onResolve,
            shared_from_this()));
}

void
    wssession::onResolve(
        beast::error_code ec,
        tcp::resolver::results_type results)
{
    if (WBASIC_DEBUG) qDebug() << "on resolve\n";
    if (ec)
        return wsfail(ec, "resolve");

    // Set the timeout for the operation
    beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

    // Make the connection on the IP address we get from a lookup
    beast::get_lowest_layer(ws_).async_connect(
        results,
        beast::bind_front_handler(
            &wssession::onConnect,
            shared_from_this()));
}

void
     wssession::onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
{
    if (WBASIC_DEBUG) qDebug() << "on connect\n";
    if (ec)
        return wsfail(ec, "connect");

    // Turn off the timeout on the tcp_stream, because
    // the websocket stream has its own timeout system.
    beast::get_lowest_layer(ws_).expires_never();

    // Set suggested timeout settings for the websocket
    ws_.set_option(
        websocket::stream_base::timeout::suggested(
            beast::role_type::client));

    // Set a decorator to change the User-Agent of the handshake
    ws_.set_option(websocket::stream_base::decorator(
        [](websocket::request_type& req)
        {
            req.set(http::field::user_agent,
                std::string(BOOST_BEAST_VERSION_STRING) +
                " websocket-client-async");
        }));

    // Update the host_ string. This will provide the value of the
    // Host HTTP header during the WebSocket handshake.
    // See https://tools.ietf.org/html/rfc7230#section-5.4
    host_ += ':' + std::to_string(ep.port());

    // Perform the websocket handshake
    ws_.async_handshake(host_, "/",
        beast::bind_front_handler(
            // call handler
            &wssession::onHandshake,
            shared_from_this()));
}

void
     wssession::onHandshake(beast::error_code ec)
{
    if (WBASIC_DEBUG) qDebug() << "on handshake\n";
    if (ec)
        return wsfail(ec, "handshake");

    // Start reading
    doRead();
}

void wssession::doRead() {
    ws_.async_read(
        buffer_,
        beast::bind_front_handler(
            // call handler when done
            &wssession::onRead,
            shared_from_this()));
}

void wssession::onRead(beast::error_code ec, std::size_t bytes_transferred)
{
    // if we are here - then reading operation is done
    if (WBASIC_DEBUG) qDebug() << "on read\n";
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return wsfail(ec, "read");

    if (need_close)
        doClose();
    else
        doSomeWork(ec, bytes_transferred);
}

void wssession::doSomeWork(beast::error_code ec, std::size_t bytes_transferred) {
    //Sleep(2000);
    //qDebug() << "LOGIC HERE | Server send to me: ";
    //
    // if there is some data from server
    if (bytes_transferred)
        qDebug() << "The server send you: " << QString::fromLocal8Bit(beast::buffers_to_string(buffer_.data()).c_str());

    // clear the buffer!
    buffer_.consume(bytes_transferred);

    // we have read some data -> then read again
    doRead();
}


void wssession::write(std::string& msg)
{
    if (WBASIC_DEBUG) qDebug() << "write\n";

    // Send the message
    ws_.async_write(
        net::buffer(msg),
        [sp = shared_from_this(), &msg](beast::error_code ec, std::size_t bytes_transferred) {
        // call handler
        sp->onWrite(ec, bytes_transferred, msg);
    });
}

void wssession::onWrite(beast::error_code ec, std::size_t bytes_transferred, std::string& msg) {
    if (ec)
        wsfail(ec, "failed while writing (write)");
    qDebug() << "You have sent: " << QString::fromLocal8Bit(msg.c_str()) << " to server. " << bytes_transferred << " bytes were delivered\n";
}

void wssession::close() {
    need_close = true;
    write(close_str); // kostil to destroy read - on_read loop
}

void wssession::doClose() {
    ws_.async_close(websocket::close_code::normal,
        beast::bind_front_handler(
            &wssession::onClose,
            shared_from_this()));
}

void wssession::onClose(beast::error_code ec)
{
    if (WBASIC_DEBUG) qDebug() << "on close\n";
    if (ec)
        return wsfail(ec, "close");

    // If we get here then the connection is closed gracefully
    qDebug() << "Connection is closed gracefully\n";
}

void runGame() {
    // -------------------------------------- [boost example]--------------------------------------

    auto const host = "127.0.0.1";
    auto const port = "8001";

    connection->run(host, port);

    // create a thread to maintain communication
//    std::thread t(
//        [&ioc]() { ioc.run(); }
//    );
//    t.detach();

    // Run the I/O service. The call will return when
    // the socket is closed.


    qDebug() << "==========\nw - write\nc - close\nm - send move json example\nCtrl + C - exit\n==========\n";

    char cmd = '\0';

    // long-living string!!!
    std::string buffer;

    std::cin >> cmd;
    qDebug() << '[' << cmd << ']' << ' ';
    switch (cmd) {
    case 'w':
        qDebug() << " write a message >> ";
        std::cin >> buffer;
        connection->write(buffer);
        sleep(2);
        qDebug() << "buffer: " << QString::fromLocal8Bit(connection->buffer().c_str());
        break;

    case 'c':
        connection->close();
        break;

    case 'm':
        buffer = "{\n\tgame_token: 21-05-26-00_11_30,\n\tuid: 21-05-26-00_11_29,\n\tprev: 12,\n\tcur: 28\n}";
        connection->write(buffer);
        break;
    }

    // -------------------------------------[ end boost example]---------------------------------

}
