#include "include/gameobjects.h"

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

// imagelabel2.cpp

ImageLabel2::ImageLabel2(QWidget *parent) :
QWidget(parent)
{
}

void ImageLabel2::paintEvent(QPaintEvent *event) {
QWidget::paintEvent(event);

if (pix.isNull())
return;

QPainter painter(this);
painter.setRenderHint(QPainter::Antialiasing);

QSize pixSize = pix.size();
pixSize.scale(event->rect().size(), Qt::KeepAspectRatio);

QPixmap scaledPix = pix.scaled(pixSize,
Qt::KeepAspectRatio,
Qt::SmoothTransformation
);

painter.drawPixmap(QPoint(), scaledPix);

}

const QPixmap* ImageLabel2::pixmap() const {
return &pix;
}

void ImageLabel2::setPixmap (const QPixmap &pixmap){
pix = pixmap;
}
