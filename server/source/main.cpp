
#include "server.h"

int main() {
    
    // common data
    const std::string ServerName("SaberLion-Devs");
    const std::string IP("127.0.0.1");
    std::string storage_root("../../storage");
    //const std::string IP("25.40.253.246");
    
    std::string http_logger(storage_root + "/http_logs/");
    std::string ws_logger(storage_root + "/ws_logs/");
    std::shared_ptr<JSON_serializer> js = std::make_shared<JSON_serializer>();
    std::shared_ptr<MatcherQueue> mq = std::make_shared<MatcherQueue>();
    std::shared_ptr<HTTP_format> hf = std::make_shared<HTTP_format>(js);
    std::shared_ptr<WS_format> ws = std::make_shared<WS_format>(js);

    // BE CAREFUL WITH FILEPATH
    Options opts_http(ServerName, IP, 8000, storage_root, http_logger);
    Options opts_ws(ServerName, IP, 8001, storage_root, ws_logger);
    Server s_http(opts_http, hf, mq);
    Server s_ws(opts_ws, ws, mq);


    const unsigned short threads_num = 1;
    asio::io_context ioc{ threads_num };

    s_http.run(ioc);
    s_ws.run(ioc);

    // Run the I/O service on the requested number of threads
    std::vector<std::thread> v;
    v.reserve(threads_num - 1);
    for (auto i = threads_num - 1; i > 0; --i)
        v.emplace_back(
            [&ioc]
            {
                ioc.run();
            });
    ioc.run();

    return 0;
}
