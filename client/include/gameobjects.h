#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QToolButton>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QObject>
#include <QLabel>

#include "community.h"

class MyButton : public QToolButton
{
    Q_OBJECT
public:
    MyButton(const QString & text = "", QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class PhotoWidget : public QLabel
{
    Q_OBJECT
public:
    PhotoWidget(QPixmap photo, QSize size = QSize(50,50), QWidget *parent = nullptr);
private:
    QPixmap photo;
    QSize size;
};

#endif // GAMEOBJECTS_H
