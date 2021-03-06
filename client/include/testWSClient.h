#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define WWBASIC_DEBUG 1


#define BOOST_DATE_TIME_NO_LIB
#include <boost/beast/core.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <thread>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

// Report a wfailure
void
wfail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Sends a WebSocket message and prints the response
class wsession : public std::enable_shared_from_this<wsession>
{
    tcp::resolver resolver_;
    websocket::stream<beast::tcp_stream> ws_;
    beast::flat_buffer buffer_;
    std::string host_;
    std::string text_;
    bool need_close = false;
    std::string close_str = "NEED_CLOSE";

public:
    // Resolver and socket require an io_context
    explicit
        wsession(net::io_context& ioc)
        : resolver_(net::make_strand(ioc))
        , ws_(net::make_strand(ioc))
    {
    }

    // Start the asynchronous operation
    void
        run(
            char const* host,
            char const* port)
    {
        if (WBASIC_DEBUG) std::cout << "run\n";
        // Save these for later
        host_ = host;
        need_close = false;

        // Look up the domain name
        resolver_.async_resolve(
            host,
            port,
            beast::bind_front_handler(
                &wsession::on_resolve,
                shared_from_this()));
    }

    void
        on_resolve(
            beast::error_code ec,
            tcp::resolver::results_type results)
    {
        if (WBASIC_DEBUG) std::cout << "on resolve\n";
        if (ec)
            return wfail(ec, "resolve");

        // Set the timeout for the operation
        beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(ws_).async_connect(
            results,
            beast::bind_front_handler(
                &wsession::on_connect,
                shared_from_this()));
    }

    void
        on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
    {
        if (WBASIC_DEBUG) std::cout << "on connect\n";
        if (ec)
            return wfail(ec, "connect");

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
                &wsession::on_handshake,
                shared_from_this()));
    }

    void
        on_handshake(beast::error_code ec)
    {
        if (WBASIC_DEBUG) std::cout << "on handshake\n";
        if (ec)
            return wfail(ec, "handshake");

        // Start reading
        do_read();
    }

    ////////
    // read
    ////////

    void do_read() {
        ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                // call handler when done
                &wsession::on_read,
                shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred)
    {
        // if we are here - then reading operation is done
        if (WBASIC_DEBUG) std::cout << "on read\n";
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return wfail(ec, "read");

        if (need_close)
            do_close();
        else
            do_some_work(ec, bytes_transferred);
    }

    ////////////////////
    // handle the answer
    ////////////////////

    void do_some_work(beast::error_code ec, std::size_t bytes_transferred) {
        //Sleep(2000);
        //std::cout << "LOGIC HERE | Server send to me: ";
        //
        // if there is some data from server
        if (bytes_transferred)
            std::cout << "The server send you: " << beast::make_printable(buffer_.data()) << std::endl;

        // clear the buffer!
        buffer_.consume(bytes_transferred);

        // we have read some data -> then read again
        do_read();
    }

    ////////
    // send
    ////////

    void write(std::string& msg)
    {
        if (WBASIC_DEBUG) std::cout << "write\n";

        // Send the message
        ws_.async_write(
            net::buffer(msg),
            [sp = shared_from_this(), &msg](beast::error_code ec, std::size_t bytes_transferred) {
            // call handler
            sp->on_write(ec, bytes_transferred, msg);
        });
    }

    void on_write(beast::error_code ec, std::size_t bytes_transferred, std::string& msg) {
        if (ec)
            wfail(ec, "wfailed while writing (write)");
        std::cout << "You have sent: " << msg << " to server. " << bytes_transferred << " bytes were delivered\n";
    }

    ////////
    // close
    ////////

    void close() {
        need_close = true;
        write(close_str); // kostil to destroy read - on_read loop
    }

    void do_close() {
        ws_.async_close(websocket::close_code::normal,
            beast::bind_front_handler(
                &wsession::on_close,
                shared_from_this()));
    }

    void on_close(beast::error_code ec)
    {
        if (WBASIC_DEBUG) std::cout << "on close\n";
        if (ec)
            return wfail(ec, "close");

        // If we get here then the connection is closed gracefully
        std::cout << "Connection is closed gracefully\n" << std::endl;
    }
};

//------------------------------------------------------------------------------

void testWSClient()
{
    // Check command line arguments.
    setlocale(LC_ALL, "rus");

    auto const host = "127.0.0.1";
    auto const port = "8001";

    // The io_context is required for all I/O
    net::io_context ioc;

    // Launch the asynchronous operation
    auto connection = std::make_shared<wsession>(ioc);
    connection->run(host, port);

    // create a thread to maintain communication
    std::thread t(
        [&ioc]() { ioc.run(); }
    );
    t.detach();

    // Run the I/O service. The call will return when
    // the socket is closed.


    std::cout << "==========\nw - write\nc - close\nm - send move json example\nCtrl + C - exit\n==========\n";

    char cmd = '\0';

    // long-living string!!!
    std::string buffer;

    while (std::cin >> cmd) {
         std::cout << '[' << cmd << ']' << ' ';
         switch (cmd) {
         case 'w':
             std::cout << " write a message >> ";
             std::cin >> buffer;
             connection->write(buffer);
             break;

         case 'C':
             connection->close();
             break;


         case 'm':
             buffer = "{\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337,\n\tprev: 12,\n\tcur: 28\n}";
             connection->write(buffer);
             break;
         case 'a':
             buffer = "{\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337,\n\tprev: 52,\n\tcur: 36\n}";
             connection->write(buffer);
             break;

             case 'b':
                 buffer = "{\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337,\n\tprev: 5,\n\tcur: 26\n}";
                 connection->write(buffer);
                 break;
             case 'c':
                 buffer = "{\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337,\n\tprev: 57,\n\tcur: 42\n}";
                 connection->write(buffer);
                 break;
             case 'd':
                 buffer = "{\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337,\n\tprev: 3,\n\tcur: 39\n}";
                 connection->write(buffer);
                 break;
             case 'e':
                 buffer = "{\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337,\n\tprev: 62,\n\tcur: 45\n}";
                 connection->write(buffer);
                 break;
             case 'f':
                 buffer = "{\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337,\n\tprev: 39,\n\tcur: 53\n}";
                 connection->write(buffer);
                 break;


          case 's':
                 buffer = "{\n\tstart,\n\tgame_token: 70-01-01-03_00_00,\n\tuid: 212281337\n}";
                 connection->write(buffer);
                 break;
         }
    }
}
