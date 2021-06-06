#include "server.h"


int main() {
    setlocale(LC_ALL, "rus");

    // common data
    const std::string ServerName("SaberLion-Devs");
    const std::string IP("127.0.0.1");
  // const std::string IP("192.168.1.26");
    // �����, ���� ���� ���������� ����
    // V ���� V
   // const std::string IP("25.34.102.253");
    // ^ ���� ^ 
    std::string storage_root = "../storage";
#ifdef _WIN32
    storage_root = "../../storage";
#endif
    
    std::string http_logger(storage_root + "/http_logs/");
    std::string ws_logger(storage_root + "/ws_logs/");
    std::shared_ptr<JSON_serializer> js = std::make_shared<JSON_serializer>();
    MQSingleton::instance();
    auto active_users = std::make_shared<UserMap>();

    // BE CAREFUL WITH FILEPATH
    Options opts_http("http", ServerName, IP, 8000, storage_root, http_logger);
    Options opts_ws("ws", ServerName, IP, 1234, storage_root, ws_logger);
    Server s_http(opts_http, active_users);
    Server s_ws(opts_ws, active_users);

    ioc_Singleton::instance();

    s_http.run(ioc_Singleton::instance().get());
    s_ws.run(ioc_Singleton::instance().get());

    ioc_Singleton::instance().get().run();

    return 0;
}
