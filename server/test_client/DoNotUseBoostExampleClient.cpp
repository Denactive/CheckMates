//------------------------------------------------------------------------------
//
// Example: HTTP client, asynchronous
//
//------------------------------------------------------------------------------

#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define BOOST_DATE_TIME_NO_LIB

#define BASIC_DEBUG 0
#define DELAY 2000
#define REPEATS 2

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <set>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Performs an HTTP GET and prints the response
class session : public std::enable_shared_from_this<session>
{
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; // (Must persist between reads)
    http::request<http::empty_body> req_;
    http::response<http::string_body> res_;

public:
    // Objects are constructed with a strand to
    // ensure that handlers do not execute concurrently.
    explicit
        session(net::io_context& ioc)
        : resolver_(net::make_strand(ioc))
        , stream_(net::make_strand(ioc))
    {
    }

    // Start the asynchronous operation
    void
        run(
            char const* host,
            char const* port,
            char const* target,
            int version)
    {
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
                &session::on_resolve,
                shared_from_this()));
    }

    void
        on_resolve(
            beast::error_code ec,
            tcp::resolver::results_type results)
    {
        if (BASIC_DEBUG) std::cout << "on resolve\n";
        if (ec)
            return fail(ec, "resolve");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(120));

        // Make the connection on the IP address we get from a lookup
        stream_.async_connect(
            results,
            beast::bind_front_handler(
                &session::on_connect,
                shared_from_this()));
    }

    void
        on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
    {
        if (BASIC_DEBUG) std::cout << "on connect\n";
        if (ec)
            return fail(ec, "connect");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(30));

        // Send the HTTP request to the remote host
        http::async_write(stream_, req_,
            beast::bind_front_handler(
                &session::on_write,
                shared_from_this()));
    }

    void
        on_write(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        if (BASIC_DEBUG) std::cout << "on write\n";
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

        // Receive the HTTP response
        http::async_read(stream_, buffer_, res_,
            beast::bind_front_handler(
                &session::on_read,
                shared_from_this()));
    }

    void
        on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
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
                &session::on_write,
                shared_from_this()));

        // If we get here then the connection is closed gracefully
    }
};

//------------------------------------------------------------------------------

int main(int argc, char** argv)
{
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
    std::string target = "/start_game/";
    auto const version = 11;
    
    // The io_context is required for all I/O
    net::io_context ioc;
    std::set<std::shared_ptr<session>> sessions;

    // Launch the asynchronous operation
    std::string cookie;
    std::cin >> cookie;
    target += cookie;

    std::make_shared<session>(ioc)->run(host, port, target, version);
    // the get operation is complete.
    ioc.run();

    system("pause");
    return EXIT_SUCCESS;
}