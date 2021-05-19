#include "net.h"


// =======================[ Serializer ]=========================


std::string JSON_serializer::serialize(std::string s) {
    return std::string("{" + s + "}");
}

std::string JSON_serializer::deserialize(std::string s) {
    return s;
}

// =======================[ Logger ]=========================


std::string FileLogger::serializeTimePoint(const time_point& time, const std::string& format)
{
    std::time_t tt = std::chrono::system_clock::to_time_t(time);
    std::tm tm;
#ifdef _WIN32
    if (localtime_s(&tm, &tt)) //Locale time-zone, usually UTC by default.
        return "undefined_time";
#else
    localtime_r(&tt, &tm); //Locale time-zone, usually UTC by default.
#endif
    char mbstr[64];
    std::stringstream ss;

    if (std::strftime(mbstr, 64, format.c_str(), &tm))
        ss << mbstr;
    else
        ss << "undefined_time";
    
    return ss.str();
}

void FileLogger::log(const std::string& data) {
    beast::error_code ec;
    try {
    if (initialized)
        log_stream_ << data;
    else throw
        beast::system_error{ beast::errc::make_error_code(beast::errc::not_connected) };
    }
    catch (beast::system_error& e) {
        ec = e.code();
        fail(ec, "logger stream is not opened");
    }
}

void FileLogger::init(beast::error_code& ec) {
    if (initialized)
        return;
    std::string filename = serializeTimePoint(std::chrono::system_clock::now(), "%y-%m-%d-%H_%M_%S") + ".txt";
    const fs::path log_file_path = dir_ / filename;
    filename = cast_filepath(log_file_path.u8string());
    log_stream_.open(filename);
    std::cout << "Log: trying to open " << filename;
    std::ofstream out(filename);
    try {
        if (!out.is_open())
            throw
            beast::system_error{ beast::errc::make_error_code(beast::errc::no_such_file_or_directory) };
    }
    catch (beast::system_error& e) {
        std::cout << " : fail" << std::endl;
        ec = e.code();
        return;
    }
    std::cout << " : success" << std::endl;
    initialized = true;
};

void FileLogger::close() {
    if (!initialized)
        return;
    log_stream_.close();
    initialized = false;
}


// =======================[ ������� ]=========================

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
