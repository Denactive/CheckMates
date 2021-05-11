//
// Created by denactive on 14.04.2021.
//

#include "net.h"


std::string JSON_serializer::serialize(std::string s) {
    return std::string("{" + s + "}");
}

std::string JSON_serializer::deserialize(std::string s) {
    return s;
}

template <typename Serializer>
void HTTP_format<Serializer>::authorize_handler() {
    std::cout<<"http::authorize" << std::endl;
    std::string serialized_data = serializer_.serialize("smtg");
}

template <typename Serializer>
void HTTP_format<Serializer>::register_handler() {
    std::cout<<"http::reg" << std::endl;
    std::string serialized_data = serializer_.serialize("smtg");
}

template <typename Serializer>
void WS_format<Serializer>::game_request_handler() {
    std::cout<<"ws::game request" << std::endl;
    std::string serialized_data = serializer_.serialize("smtg");

}

template <typename Serializer>
void WS_format<Serializer>::game_response_handler() {
    std::cout<<"ws::game response" << std::endl;
    std::string serialized_data = serializer_.serialize("smtg");
}

template <typename Serializer>
void WS_format<Serializer>::chat_handler() {
    std::cout<<"ws::chat" << std::endl;
    std::string serialized_data = serializer_.serialize("smtg");
}