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

Connection Net::accept() {
    std::cout<<"net::accept" << std::endl;
    std::string ip_str = "000.000.000.000";
    Connection con = {ip_str};
    //boost::asio::ip:: ... ("000.000.000.000");
    return con;
}

std::string Net::read() {
    std::cout<<"net::read" << std::endl;
    std::string str;
    return str;
}

void Net::write(std::string) {
    std::cout<<"net::write" << std::endl;
}

std::string JSON_serializer::serialize(std::string s) {
    return std::string("{" + s + "}");
}
std::string JSON_serializer::deserialize(std::string s) {
    return s;
}


