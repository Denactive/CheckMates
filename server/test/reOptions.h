class reOptions: public Options {
public:
    reOptions() : Options("TestOwner", "000.000.000.000", 0) {}
    MOCK_METHOD(std::string, get_info, ());
    MOCK_METHOD(void, set_port, (unsigned short port));
    MOCK_METHOD(void, set_ip, (std::string ip));
    MOCK_METHOD(void, set_owner, (std::string owner));
    MOCK_METHOD(unsigned short, get_port,());
    MOCK_METHOD(std::string, get_ip, ());
    MOCK_METHOD(std::string, get_owner, ());
};