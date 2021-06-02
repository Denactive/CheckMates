#ifdef _WIN32
#define _WIN32_WINNT 0x0A00
#endif
#define BOOST_DATE_TIME_NO_LIB

#define BASIC_DEBUG 1
#define HTTP_TIME_LIMIT 180

#include <boost/beast/core.hpp>
#include <boost/beast/core/buffers_to_string.hpp>
#include <boost/beast/websocket.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <thread>
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

//------------------------------------------------------------------------------


static bool KEEP_GOING = true;
static NewData NEW_DATA;
std::string token = "null token";
std::string game = "null gametoken";

//------------------------------------------------------------------------------




// Performs an HTTP GET and prints the response
class http_session : public std::enable_shared_from_this<http_session>
{
    tcp::resolver resolver_;
    beast::tcp_stream stream_;
    beast::flat_buffer buffer_; // (Must persist between reads)
    std::shared_ptr<http::request<http::empty_body>> req_;
    http::response<http::string_body> res_;
    std::string host_;
    std::string port_;

public:

    ~http_session() { std::cout << "http_session died\n"; }

    // Objects are constructed with a strand to
    // ensure that handlers do not execute concurrently.
    explicit
        http_session(net::io_context& ioc)
        : resolver_(net::make_strand(ioc))
        , stream_(net::make_strand(ioc))
    {
    }

    // Start the asynchronous operation
    void
        run(
            char const* host,
            char const* port)
    {
        host_ = host;
        port_ = port;
        // Set up an HTTP GET request message
        if (BASIC_DEBUG) std::cout << "http_session run\n";

        // Look up the domain name
        resolver_.async_resolve(
            host_,
            port_,
            beast::bind_front_handler(
                &http_session::on_resolve,
                shared_from_this()));
    }

    void
        on_resolve(
            beast::error_code ec,
            tcp::resolver::results_type results)
    {
        if (BASIC_DEBUG) std::cout << "http_session on resolve \n";

        if (ec)
            return fail(ec, "resolve");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(30));

        // Make the ws_connection on the IP address we get from a lookup
        stream_.async_connect(
            results,
            beast::bind_front_handler(
                &http_session::on_connect,
                shared_from_this()));
    }

    void
        on_connect(beast::error_code ec, tcp::resolver::results_type::endpoint_type)
    {
        if (BASIC_DEBUG) std::cout << "http_session on_connect \n";

        if (ec)
            return fail(ec, "connect");

        // Set a timeout on the operation
        stream_.expires_after(std::chrono::seconds(HTTP_TIME_LIMIT));
        std::cout << "Connected\n";
    }

    void
        write(std::string target)
    {
        if (BASIC_DEBUG) std::cout << "http_session get: " << target << "\n";

        if (!KEEP_GOING)
            return close();
        // Send the HTTP request to the remote host
        req_ = std::make_shared< http::request < http::empty_body>>();
        req_->version(11);
        req_->method(http::verb::get);
        req_->set(http::field::host, host_);
        req_->set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);

        std::cout << "\nREQUEST is built!\nHEADER:\n" << req_->base() << "BODY:\n" << "No Body\n===============================\n" << std::endl;
        req_->target(target);

        http::async_write(stream_, *req_,
            beast::bind_front_handler(
                &http_session::on_write,
                shared_from_this()));
    }

    void on_write(
        beast::error_code ec,
        std::size_t bytes_transferred)
    {
        if (BASIC_DEBUG) std::cout << "http_session on_write\n";
        if (!KEEP_GOING)
            return close();

        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "write");

        // Receive the HTTP response
        http::async_read(stream_, buffer_, res_,
            beast::bind_front_handler(
                &http_session::on_read,
                shared_from_this()));
    }

    void
        on_read(
            beast::error_code ec,
            std::size_t bytes_transferred)
    {
        if (BASIC_DEBUG) std::cout << "http_session on_read\n";

        boost::ignore_unused(bytes_transferred);

        if (ec)
            return fail(ec, "read");

        // Write the message to standard out
        std::cout << "http-server responsed: \n" << res_.body() << "\n";
        auto cookie_beg = res_.body().find("Cookie: ");
        if (cookie_beg != std::string::npos) {
            auto cookie_end = res_.body().substr(cookie_beg + 8).find('\n');
            auto token_local = res_.body().substr(cookie_beg + 8, cookie_end);
            token = token_local;
            std::cout << "Got token: " << token << std::endl;
            cookie_beg = std::string::npos;
        }

        auto gt_beg = res_.body().find("game_token: ");
        if (gt_beg != std::string::npos) {
            gt_beg += 12;
            auto gt_end = res_.body().substr(gt_beg).find(',');
            game = res_.body().substr(gt_beg, gt_end);
            std::cout << "Game token: " << game << "\n";
            gt_beg = std::string::npos;
        }
        res_.body() = "";
    }

    void close() {
        if (BASIC_DEBUG) std::cout << "http_session close\n";

        // Gracefully close the socket
        beast::error_code ec;
        stream_.socket().shutdown(tcp::socket::shutdown_both, ec);
        // not_connected happens sometimes so don't bother reporting it.
        if (ec && ec != beast::errc::not_connected)
            return fail(ec, "shutdown");
    }
};


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
    ~session() { std::cout << "ws_session died\n"; }


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

        // Make the ws_connection on the IP address we get from a lookup
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

        // If we get here then the ws_connection is closed gracefully
        std::cout << "ws_connection is closed gracefully\n" << std::endl;
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
    auto ws_connection = std::make_shared<session>(ioc);
    ws_connection->run(host, "1234");

    auto http_connection = std::make_shared<http_session>(ioc);
    http_connection->run(host, "8000");

    // create a thread to maintain communication
    std::thread t(
        [&ioc]() { ioc.run(); }
    );
    //t.detach();

    // Run the I/O service. The call will return when
    // the socket is closed.


    char cmd = '\0';

    // long-living string!!!
    std::string buffer;
    std::string http_buffer;
    bool skip_waiting = false;

#ifdef _WIN32
    Sleep(500);
#else 
    sleep(1);
#endif // WIN32

    std::cout << "Set user [1] - Sveta, [2] - Denis, [3] - Youra >> ";
    int uid = 0;
    std::cin >> uid;
    if (uid > 3)
        uid = 1;
    std::string names[] = { "Sveta", "Denis", "Youra" };

    std::cout << "==========\n1 - http login\n2 - http connect\n==========\n";
    std::cout << "==========\nw - ws write\nC - ws close\nm - send move json example\nE - exit\n==========\n";

    while (KEEP_GOING) {
        skip_waiting = false;

        std::cin >> cmd;
        std::cout << '[' << cmd << ']' << ' ';
        switch (cmd) {

        case '1':
            http_buffer = "/register/" + names[uid - 1];
            http_connection->write(http_buffer);
            skip_waiting = true;
            break;

        case '2':
            http_buffer = "/start_game/" + token;
            http_connection->write(http_buffer);
            skip_waiting = true;
            break;

        case 'w':
            std::cout << " write a message >> ";
            std::cin >> buffer;
            ws_connection->write(buffer);
            break;

        case '�':
            ws_connection->close();
            break;

        case 'm':
            buffer = "{\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + ",\n\tprev: 12,\n\tcur: 28\n}";
            ws_connection->write(buffer);
            break;

        case 'E':
            KEEP_GOING = false;
            ws_connection->close();
            break;

        case 'a':
            buffer = "{\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + ",\n\tprev: 52,\n\tcur: 36\n}";
            ws_connection->write(buffer);
            break;

        case 'b':
            buffer = "{\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + ",\n\tprev: 5,\n\tcur: 26\n}";
            ws_connection->write(buffer);
            break;

        case 'c':
            buffer = "{\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + ",\n\tprev: 57,\n\tcur: 42\n}";
            ws_connection->write(buffer);
            break;

        case 'd':
            buffer = "{\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + ",\n\tprev: 3,\n\tcur: 39\n}";
            ws_connection->write(buffer);
            break;

        case 'e':
            buffer = "{\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + ",\n\tprev: 62,\n\tcur: 45\n}";
            ws_connection->write(buffer);
            break;

        case 'f':
            buffer = "{\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + ",\n\tprev: 39,\n\tcur: 53\n}";
            ws_connection->write(buffer);
            break;

        case 's':
            buffer = "{\n\tstart,\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + "\n}";
            ws_connection->write(buffer);
            break;

        case 'p':
            buffer = "{\n\tprepare,\n\tgame_token: " + game + ",\n\tuid: " + std::to_string(uid) + "\n}";
            ws_connection->write(buffer);
            break;

        default:
            skip_waiting = true;
        }

        if (!skip_waiting) {
            // wait for response
            while (!NEW_DATA.state());
            NEW_DATA.set(false);
            std::cout << "I am standart thread. I've got a message from server:\n" << msg_Singleton::instance().get() << std::endl;
        }
    }

    t.join();

    system("pause");
    return EXIT_SUCCESS;
}