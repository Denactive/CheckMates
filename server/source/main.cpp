
#include "server.h"

int main() {
    
    // common data
    const std::string ServerName("SaberLion-Devs");
    const std::string IP("127.0.0.1");
    std::string storage_root("../../storage");
    //const std::string IP("25.40.253.246");
    
    std::shared_ptr<FileLogger> http_logger = std::make_shared<FileLogger>(storage_root + std::string("/logs/http_conversation"));
    std::shared_ptr<FileLogger> ws_logger = std::make_shared<FileLogger>(storage_root + std::string("/logs/ws_conversation/"));
    std::shared_ptr<FileLogger> read_logger = std::make_shared<FileLogger>(storage_root + std::string("/logs/connections/"));
    std::shared_ptr<FileLogger> write_logger = std::make_shared<FileLogger>(storage_root + std::string("/logs/answers/"));
    std::shared_ptr<JSON_serializer> js = std::make_shared<JSON_serializer>();
    std::shared_ptr<MatcherQueue> mq = std::make_shared<MatcherQueue>();
    std::shared_ptr<HTTP_format> hf = std::make_shared<HTTP_format>(js, http_logger);
    std::shared_ptr<WS_format> ws = std::make_shared<WS_format>(js, ws_logger);

    // BE CAREFUL WITH FILEPATH
    Options opts_http(ServerName, IP, 8000, storage_root);
    Options opts_ws(ServerName, IP, 8001, storage_root);
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
