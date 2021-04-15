#include "../include/graphics.h"
#include "../include/chessboard.h"
#include <iostream>

bool TEST(std::string testName, bool (*f)(), std::string status) {
    if (f() != true) {
        std::cout << "TEST " << testName << "." << status << " FAIL\n";
        return false;

    } else {
        std::cout << "TEST " << testName  << "." << status <<  " SUCCESS\n";
    }
    return true;
}

bool HAS_FIGURE() {
    Cell cell;
    Figure figure;
    cell.setFigure(&figure);
    return cell.isHasFigure() == true;
}

bool NOT_SET_COLOR() {
    Cell cell;
    cell.setColor("blue");
    return cell.getColor() != "red";
}

bool IS_BORDER_OF_BROAD() {
    ChessBoard board(8);
    return (board.isBorderOfBoard(9) == true);
}

bool CORRECT_PASSWORD() {
//    User user;
   // user.setPassowrd("111");
    return true;
//    return (user.getUserPassword() == "111");
}

bool tests() {
    bool testsIsRun = true;

    if (!TEST("HAS_FIGURE", HAS_FIGURE, "ok")) testsIsRun = false;
    if (!TEST("NOT_SET_COLOR", NOT_SET_COLOR, "not_ok")) testsIsRun = false;
    if (!TEST("IS_BORDER_OF_BROAD", IS_BORDER_OF_BROAD, "ok")) testsIsRun = false;

    return testsIsRun;
}
