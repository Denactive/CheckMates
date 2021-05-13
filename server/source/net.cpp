#include "net.h"


// =======================[ Serializer ]=========================


std::string JSON_serializer::serialize(std::string s) {
    return std::string("{" + s + "}");
}

std::string JSON_serializer::deserialize(std::string s) {
    return s;
}

// =======================[ Logger ]=========================




// =======================[ Затычки ]=========================

//template <typename Serializer>
//void HTTP_format<Serializer>::authorize_handler() {
void HTTP_format::authorize_handler() {
    std::cout<<"http::authorize" << std::endl;
    std::string serialized_data = serializer_->serialize("smtg");
}

//template <typename Serializer>
//void HTTP_format<Serializer>::register_handler() {
void HTTP_format::register_handler() {
    std::cout<<"http::reg" << std::endl;
    std::string serialized_data = serializer_->serialize("smtg");
}

//template <typename Serializer>
//void WS_format<Serializer>::game_request_handler() {
void WS_format::game_request_handler() {
    std::cout<<"ws::game request" << std::endl;
    //std::string serialized_data = serializer_->serialize("smtg");

}

void WS_format::game_response_handler() {
    //template <typename Serializer>
//void WS_format<Serializer>::game_response_handler() {
    std::cout<<"ws::game response" << std::endl;
    //std::string serialized_data = serializer_->serialize("smtg");
}

void WS_format::chat_handler() {
    //template <typename Serializer>
//void WS_format<Serializer>::chat_handler() {
    std::cout<<"ws::chat" << std::endl;
    //std::string serialized_data = serializer_->serialize("smtg");
}