#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <iostream>

#include "../include/community.h"
#include "../include/chessboard.h"
#include "../include/figures.h"
#include "../include/gamewindowswork.h"
#include "../include/mainwindow.h"
#include "../include/database.h"
#include "ui_mainwindow.h"

class IGraphics
{
public:
    void StartDraw();
    void cleanAll();
    bool getData(char ** figures, User* user, Chat * chat);
};

class Graphics
{
private:
    User * user;
    char ** figures;
    Chat *chats;
public:
    Graphics();
    void StartDraw();
    void cleanAll();
    bool getData(char ** figures, User* user, Chat * chat);
};

#endif // GRAPHICS_H
