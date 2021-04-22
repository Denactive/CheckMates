class reSerializer {
public:
    MOCK_METHOD(std::string, serialize, (std::string));
    MOCK_METHOD(std::string, deserialize, (std::string));
};
