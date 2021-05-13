#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <string>
#include <vector>
#include <iostream>

#include "../include/community.h"
#include "../include/chessboard.h"
#include "../include/figures.h"
#include "../include/windows/mainwindow.h"
#include "../include/database.h"

class IGraphics
{
public:
    virtual void StartDraw() = 0;
    virtual void cleanAll() = 0;
    virtual bool getData(char ** figures, User* user, Chat * chats) = 0;
};

class Graphics : public IGraphics
{
private:
    User * user;
    char ** figures;
    Chat *chats;
public:
    Graphics(char ** nfigures = nullptr, User * nuser = nullptr, Chat * nchats = nullptr)
        :user(nuser), figures(nfigures), chats(nchats) {}
    void StartDraw() override {}
    void cleanAll() override {}
    bool getData(char ** figures, User* user, Chat * chats) override { return true; }
};

#endif // GRAPHICS_H
