#include "server.h"


int main() {
    setlocale(LC_ALL, "rus");

    // common data
    const std::string ServerName("SaberLion-Devs");
    const std::string IP("127.0.0.1");
//    const std::string IP("192.168.1.26");
    std::string storage_root = "../storage";
#ifdef _WIN32
    storage_root = "../../storage";
#endif
    //const std::string IP("25.40.253.246");
    std::string http_logger(storage_root + "/http_logs/");
    std::string ws_logger(storage_root + "/ws_logs/");
    std::shared_ptr<JSON_serializer> js = std::make_shared<JSON_serializer>();
    std::shared_ptr<MatcherQueue> mq = std::make_shared<MatcherQueue>();
    auto active_users = std::make_shared<UserMap>();

    std::shared_ptr<HTTP_format> hf = std::make_shared<HTTP_format>(js, mq);
    std::shared_ptr<WS_format> ws = std::make_shared<WS_format>(js, mq);

    // BE CAREFUL WITH FILEPATH
    Options opts_http("http", ServerName, IP, 8000, storage_root, http_logger);
    Options opts_ws("ws", ServerName, IP, 8001, storage_root, ws_logger);
    Server s_http(opts_http, hf, active_users);
    Server s_ws(opts_ws, ws, active_users);

    ioc_Singleton::instance();

    s_http.run(ioc_Singleton::instance().get());
    s_ws.run(ioc_Singleton::instance().get());

    ioc_Singleton::instance().get().run();

    return 0;
}
