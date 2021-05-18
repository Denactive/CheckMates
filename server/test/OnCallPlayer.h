rePlayer player;
ON_CALL(player, try_move())
.WillByDefault(Return(true));
ON_CALL(player, is_check())
.WillByDefault(Return(false));
ON_CALL(player, is_mate())
.WillByDefault(Return(false));
ON_CALL(player, is_stalemate())
.WillByDefault(Return(false));
ON_CALL(player, GetUserId())
.WillByDefault(Return(0));
std::vector<std::string> vec;
vec.push_back("new");
ON_CALL(player, all_available_Moves())
.WillByDefault(Return(vec));