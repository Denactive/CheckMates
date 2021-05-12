
#include "server.h"

int main() {
    
    // common data
    const std::string ServerName("SaberLion-Devs");
    const std::string IP("127.0.0.1");
    //const std::string IP("25.40.253.246");
    //std::shared_ptr<JSON_serializer> js = std::make_shared<JSON_serializer>();
    ISerializer* js = new JSON_serializer();
    //std::shared_ptr<MatcherQueue> mq = std::make_shared<MatcherQueue>();
    IMatcherQueue* mq = new MatcherQueue();
    HTTP_format hf(js);
    //WS_format wf(js);

    
    // BE CAREFUL WITH FILEPATH
    Options opts_http(ServerName, IP, 8000, "C:/Users/Denactive/source/repos/SaberDevs_CheckMates/server/storage");
    Options opts_ws(ServerName, IP, 8001, "C:/Users/Denactive/source/repos/SaberDevs_CheckMates/server/storage");
    // Server(Options opts, IFormat & format, IMatcherQueue & matcher_queue)
    Server s_http(opts_http, &hf, mq);
    // TODO: WS_FORMAT
    Server s_ws(opts_ws, &hf, mq);
    
    ChessBoard board;
    board.set_board();
    Player player1(board, true);
    Player player2(board, false);
    TurnControl control;
    GameSession A(control, player1, player2);
    A.run();

    const unsigned short threads_num = 1;
    asio::io_context ioc{ threads_num };

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

    // run 
    s_http.run(ioc);
    s_ws.run(ioc);

    return 0;
}
