#include "include/gameobjects.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

MyButton::MyButton(const QString &text, QWidget *parent) :QToolButton(parent)
{
    setText(text);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    style = "background-color: #ACCCC4; border: 2px solid #464545; border-radius: 10%; ";
    setStyleSheet(style);
}

QSize MyButton::sizeHint() const
{
    QSize size = QToolButton::sizeHint();
    size.rheight() += 30;
    size.rwidth() = qMax(size.width(), size.height());
    return size;
}

void MyButton::addStyle(QString newStyle)
{
    style += newStyle;
    setStyleSheet(style);
}

PhotoWidget::PhotoWidget(QPixmap photo, QSize size, QWidget *parent)
    :QLabel(parent), photo(photo), size(size)
{
    this->photo = photo.scaled(size, Qt::KeepAspectRatio);
    setPixmap(this->photo);

    QLabel::resize(size);
}

QSize PhotoWidget::sizeHint() const
{
    return this->size;
}

FrameButton::FrameButton(QWidget *parent, std::shared_ptr<Chat> chat)
    :QFrame(parent), chat(chat)
{
    this->setStyleSheet("background-color: #E2DFD8;");
    this->setFrameStyle(QFrame::Box);
    this->setFrameShadow(QFrame::Raised);
    this->setLineWidth(3);
}

void FrameButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

void LabelImage::resizeLabel(QResizeEvent *event)
{
   QLabel::resizeEvent(event);
   QRect rect(QApplication::desktop()->screenGeometry());
   if (event->size().width() < rect.width() && event->size().height() < rect.height()) {
       this->setPixmap(_qPixmap, event->size());
       this->setSize(event->size());
   } else {
   }
}

void LabelImage::resizeEvent(QResizeEvent *event)
{
    // qDebug() << "resize event";
}

void LabelImage::setPixmap(const QPixmap &qPixmap, const QSize &size)
{
  _qPixmap = qPixmap;
  _qPixmapScaled = _qPixmap.scaled(size, Qt::KeepAspectRatio);
  QLabel::setPixmap(_qPixmapScaled);
}
