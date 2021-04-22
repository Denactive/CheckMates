class rePlayer: public iPlayer {
public:
    MOCK_METHOD(std::vector<std::string>, all_available_Moves, ());
    MOCK_METHOD(bool, try_move, ());
    MOCK_METHOD(bool, is_check, ());
    MOCK_METHOD(bool, is_mate, ());
    MOCK_METHOD(bool, is_stalemate, ());
    MOCK_METHOD(void, set_pieces, ());
    MOCK_METHOD(size_t, GetUserId, ());
};
