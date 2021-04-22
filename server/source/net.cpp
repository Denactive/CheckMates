//
// Created by denactive on 14.04.2021.
//

#include "net.h"

void HTTP_format::run() {
    std::cout<<"http::run" << std::endl;
}
void HTTP_format::request_handler() {
    std::cout<<"http::request" << std::endl;
}
void HTTP_format::authorize_handler() {
    std::cout<<"http::authorize" << std::endl;
}
void HTTP_format::register_handler() {
    std::cout<<"http::reg" << std::endl;
}
