#include "include/gameobjects.h"

#include <QDebug>

MyButton::MyButton(const QString &text, QWidget *parent) :QToolButton(parent)
{
    setText(text);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
}

QSize MyButton::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

PhotoWidget::PhotoWidget(QPixmap photo, QSize size, QWidget *parent)
    :QLabel(parent), photo(photo), size(size)
{
    this->photo = photo.scaled(size, Qt::KeepAspectRatio);
    setPixmap(this->photo);

    qDebug() << "size " << QLabel::width() << " " << QLabel::height();
    QLabel::resize(size);
    qDebug() << "size " << QLabel::width() << " " << QLabel::height();
}

QSize PhotoWidget::sizeHint() const
{
    return this->size;
}

ChatButton::ChatButton(QWidget *parent)
    :QFrame(parent)
{
    //this->setFrameStyle(QFrame::Panel);
    //this->setFrameShadow(QFrame::Raised);
    //this->setLineWidth(2);
}
