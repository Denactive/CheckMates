#include "net.h"


// =======================[ Serializer ]=========================


std::string JSON_serializer::serialize(std::string s) {
    return std::string("{" + s + "}");
}

std::string JSON_serializer::deserialize(std::string s) {
    return s;
}

// =======================[ Logger ]=========================

void FileLogger::log(const std::string& data) {
    beast::error_code ec;
    this->init(ec);
    if (ec)
        fail(ec, "unable to init log");
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

FileLogger::~FileLogger() {
    this->close();
}