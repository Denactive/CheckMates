#include "gameobjects.h"

MyButton::MyButton(const QString &text, QWidget *parent)
{
    setText(text);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
}
