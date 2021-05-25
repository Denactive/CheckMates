#include "include/wsclient.h"

// Start the asynchronous operation
void wssession::run(char const* host, char const* port, char const* text)
{
    if (WBASIC_DEBUG) std::cout << "run\n";
    // Save these for later
    host_ = host;
    text_ = text;

    // Look up the domain name
    resolver_.async_resolve(
        host,
        port,
        beast::bind_front_handler(
            &wssession::onResolve,
            shared_from_this()));
}

void wssession::onResolve(beast::error_code ec, tcp::resolver::results_type results) {
    if (WBASIC_DEBUG) std::cout << "on resolve\n";
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

void wssession::onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep) {
    if (WBASIC_DEBUG) std::cout << "on connect\n";
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
            &wssession::onHandshake,
            shared_from_this()));
}

void wssession::onHandshake(beast::error_code ec) {
    if (WBASIC_DEBUG) std::cout << "on handshake\n";
    if (ec)
        return wsfail(ec, "handshake");

    // Send the message
    ws_.async_write(
        net::buffer(text_),
        beast::bind_front_handler(
            &wssession::onWrite,
            shared_from_this()));
}

void wssession::onWrite(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (WBASIC_DEBUG) std::cout << "on write\n";
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return wsfail(ec, "write");

    // Read a message into our buffer
    ws_.async_read(
        buffer_,
        beast::bind_front_handler(
            &wssession::onRead,
            shared_from_this()));
}

void wssession::onRead(beast::error_code ec, std::size_t bytes_transferred) {
    boost::ignore_unused(bytes_transferred);

    if (WBASIC_DEBUG) std::cout << "on read\n";
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return wsfail(ec, "read");

    // Close the WebSocket connection
    /*ws_.async_close(websocket::close_code::normal,
        beast::bind_front_handler(
            &session::on_close,
            shared_from_this()));
    */
    doSomeWork();
}

void wssession::onClose(beast::error_code ec) {
    if (WBASIC_DEBUG) std::cout << "on close\n";
    if (ec)
        return wsfail(ec, "close");

    // If we get here then the connection is closed gracefully

    // The make_printable() function helps print a ConstBufferSequence
    std::cout << beast::make_printable(buffer_.data()) << std::endl;
}

void wssession::doSomeWork() {
    sleep(2);

    std::cin >> text_;
    std::cout << "LOGIC HERE | Server send to me: ";
    std::cout << beast::make_printable(buffer_.data()) << std::endl;

    buffer_.consume(buffer_.size());

    auto msg = std::make_shared<std::string>("WS from client: " + text_);// +*recieved;
    ws_.text(ws_.got_text());
    ws_.async_write(
        net::buffer(*msg),
        [s = shared_from_this(), msg] (beast::error_code ec, size_t bytes_transferred) mutable {
            s->onWrite(ec, msg->size());
        }
    );

    /*ws_.async_write(
        net::buffer(text_),
        beast::bind_front_handler(
            &wssession::onWrite,
            shared_from_this()));*/
}

void wsfail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}
