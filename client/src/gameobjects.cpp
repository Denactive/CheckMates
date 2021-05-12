#include "include/gameobjects.h"

#include <QDebug>

MyButton::MyButton(const QString &text, QWidget *parent) :QToolButton(parent)
{
    setText(text);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
//    setStyleSheet("border-image: url(../img/black_chess.png) 0 0 0 0 scretch; color: red; background-position: center; ");

//    QRect rect(0, 0, 1000, 1000);
    //QPixmap sprite;
    //sprite.load("../img/black_chess.png");
    //sprite.setGe
//    QPixmap pix = sprite.copy(rect);
//    QSize pixSize(sizeHint());
//    pix.scaled(pixSize);
//    setIcon(pix);
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
    //parent->resize(size);

    qDebug() << "size " << QLabel::width() << " " << QLabel::height();
    QLabel::resize(size);
    qDebug() << "size " << QLabel::width() << " " << QLabel::height();
}

QSize PhotoWidget::sizeHint() const
{
    return this->size;
}
