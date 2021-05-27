#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif

#define BASIC_DEBUG 1


#define BOOST_DATE_TIME_NO_LIB
#include <boost/beast/core.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <mutex>

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace websocket = beast::websocket; // from <boost/beast/websocket.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>

//------------------------------------------------------------------------------

struct NewData
{
    bool state() {
        std::lock_guard<std::recursive_mutex> locker(mtx_new_data_);
        return flg;
    }
    void set(bool val) {
        std::lock_guard<std::recursive_mutex> locker(mtx_new_data_);
        flg = val;
    }
private:
    std::recursive_mutex mtx_new_data_;
    bool flg = false;
};

static bool KEEP_GOING = true;
static NewData NEW_DATA;

class msg_Singleton
{
public:
    static msg_Singleton& instance()
    {
        static msg_Singleton singleton;
        return singleton;
    }

    std::string& get() { return msg; }
    
    void set(std::string& text) {
        std::lock_guard<std::recursive_mutex> locker(mtx_);
        msg = text;
    }

    // Other non-static member functions
private:
    msg_Singleton() {}                                  // Private constructor
    ~msg_Singleton() {}
    msg_Singleton(const msg_Singleton&);                 // Prevent copy-construction
    msg_Singleton& operator=(const msg_Singleton&);      // Prevent assignment
    std::string msg;
    std::recursive_mutex mtx_;
};

// Report a failure
void
fail(beast::error_code ec, char const* what)
{
    std::cerr << what << ": " << ec.message() << "\n";
}

// Sends a WebSocket message and prints the response
class session : public std::enable_shared_from_this<session>
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
        session(net::io_context& ioc)
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
        if (BASIC_DEBUG) std::cout << "run\n";
        // Save these for later
        host_ = host;
        need_close = false;

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

        // Set the timeout for the operation
        beast::get_lowest_layer(ws_).expires_after(std::chrono::seconds(30));

        // Make the connection on the IP address we get from a lookup
        beast::get_lowest_layer(ws_).async_connect(
            results,
            beast::bind_front_handler(
                &session::on_connect,
                shared_from_this()));
    }

    void
        on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type ep)
    {
        if (BASIC_DEBUG) std::cout << "on connect\n";
        if (ec)
            return fail(ec, "connect");

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
                &session::on_handshake,
                shared_from_this()));
    }

    void
        on_handshake(beast::error_code ec)
    {
        if (BASIC_DEBUG) std::cout << "on handshake\n";
        if (ec)
            return fail(ec, "handshake");

        // Start reading
        do_read();
    }

    ////////
    // read
    ////////

    void do_read() {
        if (!KEEP_GOING)
            return close();

        ws_.async_read(
            buffer_,
            beast::bind_front_handler(
                // call handler when done
                &session::on_read,
                shared_from_this()));
    }

    void on_read(beast::error_code ec, std::size_t bytes_transferred)
    {
        // if we are here - then reading operation is done
        if (BASIC_DEBUG) std::cout << "on read\n";
        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "read");

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
        if (bytes_transferred) {
            std::string msg = beast::buffers_to_string(buffer_.data());
            msg_Singleton::instance().set(msg);
            //try static
            std::cout << "The server send you: " << beast::make_printable(buffer_.data()) << std::endl;
            NEW_DATA.set(true);
        }
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
        if (BASIC_DEBUG) std::cout << "write\n";

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
            fail(ec, "failed while writing (write)");
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
                &session::on_close,
                shared_from_this()));
    }

    void on_close(beast::error_code ec)
    {
        if (BASIC_DEBUG) std::cout << "on close\n";
        if (ec)
            return fail(ec, "close");

        // If we get here then the connection is closed gracefully
        std::cout << "Connection is closed gracefully\n" << std::endl;
    }
};

//------------------------------------------------------------------------------

int main(int argc, char** argv)
{
    // Check command line arguments.
    setlocale(LC_ALL, "rus");

    auto const host = "127.0.0.1";
    auto const port = "8001";

    // The io_context is required for all I/O
    msg_Singleton::instance();
    net::io_context ioc;

    // Launch the asynchronous operation
    auto connection = std::make_shared<session>(ioc);
    connection->run(host, port);

    // create a thread to maintain communication
    std::thread t(
        [&ioc]() { ioc.run(); }
    );
    //t.detach();

    // Run the I/O service. The call will return when
    // the socket is closed.


    std::cout << "==========\nw - write\nc - close\nm - send move json example\ne - exit\n==========\n";

    char cmd = '\0';

    // long-living string!!!
    std::string buffer;

    while (KEEP_GOING) {

        //std::cout << "\tfuck: " << NEW_DATA.state() << std::endl;

        

        std::cin >> cmd;
        std::cout << '[' << cmd << ']' << ' ';
        switch (cmd) {
        case 'w':
            std::cout << " write a message >> ";
            std::cin >> buffer;
            connection->write(buffer);
            break;

        case 'c':
            connection->close();
            break;

        case 'm':
            buffer = "{\n\tgame_token: 21-05-26-00_11_30,\n\tuid: 21-05-26-00_11_29,\n\tprev: 12,\n\tcur: 28\n}";
            connection->write(buffer);
            break;

        case 'e':
            KEEP_GOING = false;
            connection->close();
            break;
        }

        // wait for response
        while (!NEW_DATA.state());
        NEW_DATA.set(false);
        std::cout << "I am standart thread. I've got a message from server:\n" << msg_Singleton::instance().get();
    }

    t.join();

    system("pause");
    return EXIT_SUCCESS;
}