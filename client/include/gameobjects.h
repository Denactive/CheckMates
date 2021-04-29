#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QToolButton>

class MyButton : public QToolButton
{
    Q_OBJECT
public:
    MyButton(const QString & text = "", QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

#endif // GAMEOBJECTS_H
