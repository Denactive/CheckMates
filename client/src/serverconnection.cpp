#include "include/serverconnection.h"

// Start the asynchronous operation
void session::run(char const* host, char const* port, char const* target, int version) {
    if (BASIC_DEBUG) std::cout << "run\n";
    // Set up an HTTP GET request message
    req_.version(version);
    req_.method(http::verb::get);
    req_.target(target);
    req_.set(http::field::host, host);
    req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
    req_.method(http::verb::get);

    std::cout << "\nREQUEST is built!\nHEADER:\n" << req_.base() << "BODY:\n" << "No Body\n===============================\n" << std::endl;

    // Look up the domain name
    resolver_.async_resolve(
        host,
        port,
        beast::bind_front_handler(
            &session::onResolve,
            shared_from_this()));
}

void session::onResolve(beast::error_code ec, tcp::resolver::results_type results) {
    if (BASIC_DEBUG) std::cout << "on resolve\n";
    if (ec)
        return fail(ec, "resolve");

    // Set a timeout on the operation
    stream_.expires_after(std::chrono::seconds(120));

    // Make the connection on the IP address we get from a lookup
    stream_.async_connect(
        results,
        beast::bind_front_handler(
            &session::onConnect,
            shared_from_this()));
}

void session::onConnect(beast::error_code ec, tcp::resolver::results_type::endpoint_type) {
    if (BASIC_DEBUG) std::cout << "on connect\n";
    if (ec)
        return fail(ec, "connect");

    // Set a timeout on the operation
    stream_.expires_after(std::chrono::seconds(30));

    // Send the HTTP request to the remote host
    http::async_write(stream_, req_,
        beast::bind_front_handler(
            &session::onWrite,
            shared_from_this()));
}

void session::onWrite(beast::error_code ec, std::size_t bytes_transferred) {
    if (BASIC_DEBUG) std::cout << "on write\n";
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

        // Receive the HTTP response
        http::async_read(stream_, buffer_, res_,
            beast::bind_front_handler(
                &session::onRead,
                shared_from_this()));
}

void session::onRead(beast::error_code ec, std::size_t bytes_transferred) {
    if (BASIC_DEBUG) std::cout << "on read\n";
    boost::ignore_unused(bytes_transferred);

    if (ec)
        return fail(ec, "read");

    // Write the message to standard out
    std::cout << res_ << std::endl;

    // Gracefully close the socket
    stream_.socket().shutdown(tcp::socket::shutdown_both, ec);

    // not_connected happens sometimes so don't bother reporting it.
    if (ec && ec != beast::errc::not_connected)
        return fail(ec, "shutdown");

    http::async_write(stream_, req_,
        beast::bind_front_handler(
            &session::onWrite,
            shared_from_this()));

    // If we get here then the connection is closed gracefully
}

void fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}
