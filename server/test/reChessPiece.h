class reChessPiece: public ChessPiece {
public:
    MOCK_METHOD(void, move, ());
    MOCK_METHOD(std::vector<std::string>, available_moves, ());
    MOCK_METHOD(void, capture_piece, ());
    MOCK_METHOD(bool, is_check, ());
    MOCK_METHOD(bool, is_stalemate, ());
    MOCK_METHOD(bool, is_mate, ());
};





