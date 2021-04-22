//
// Created by denactive on 14.04.2021.
//

#include "net.h"

void HTTP_format::run() {
    std::cout<<"http::run" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");
}
void HTTP_format::request_handler() {
    std::cout<<"http::request" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");
}
void HTTP_format::authorize_handler() {
    std::cout<<"http::authorize" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");
}
void HTTP_format::register_handler() {
    std::cout<<"http::reg" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");
}

void WS_format::run() {
    std::cout<<"ws::run" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");
}
void WS_format::game_request_handler() {
    std::cout<<"ws::game request" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");

}
void WS_format::game_response_handler() {
    std::cout<<"ws::game response" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");
}
void WS_format::chat_handler() {
    std::cout<<"ws::chat" << std::endl;
    std::string serialized_data = serializer.serialize("smtg");
}
