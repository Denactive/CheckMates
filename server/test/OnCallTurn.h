reTurnControl control;
ON_CALL(control, GetTime(true))
.WillByDefault(Return(100));
ON_CALL(control, GetTurn())
.WillByDefault(Return(true));
