#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <string>
#include <vector>
#include <iostream>
#include <QPixmap>
#include <QMainWindow>
#include <QDialog>
#include <QMessageBox>
#include <QDebug>
#include <QAbstractListModel>
#include "community.h"
#include "chessboard.h"
#include "figures.h"
#include "gamewindowswork.h"
#include "mainwindow.h"
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

/*
Необходимые входные данные от Юры:
Массив расстановки фигур char*[8][8]
Каждый чар: 1 символ - название фигуры(большая буква - белый/ маленькая - черный)
От Ксюши: информация о User'ах (список всех юзеров): пароль, логин, никнейм, рейтинг, время в игре
класс Chat: имя друга (стринг),
история сообщений: массив класссов Message
поля Message: время сообщения (инт), само сообщение (стринг), принадлежность пользователю (стринг)
 */
