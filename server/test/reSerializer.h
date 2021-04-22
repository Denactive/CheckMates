class reSerializer: public ISerializer {
public:
    MOCK_METHOD(std::string, serialize, (std::string), (override));
    MOCK_METHOD(std::string, deserialize, (std::string), (override));
};
