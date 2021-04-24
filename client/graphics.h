#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <iostream>

#include "include/community.h"
#include "include/chessboard.h"
#include "include/figures.h"
#include "include/gamewindowswork.h"
#include "mainwindow.h"
#include "include/database.h"
#include "ui_mainwindow.h"

class IGraphics
{
public:
    virtual void StartDraw() = 0;
    virtual void cleanAll() = 0;
    virtual bool getData(char ** figures, User* user, Chat * chat) = 0;
};

class Graphics : public IGraphics
{
private:
    User * user;
    char ** figures;
    Chat *chats;
public:
    Graphics();
    void StartDraw() override;
    void cleanAll() override;
    bool getData(char ** figures, User* user, Chat * chat) override;
};

#endif // GRAPHICS_H
