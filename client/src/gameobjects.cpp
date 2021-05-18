#include "include/gameobjects.h"

#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

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

    // qDebug() << "size " << QLabel::width() << " " << QLabel::height();
    QLabel::resize(size);
    // qDebug() << "size " << QLabel::width() << " " << QLabel::height();
}

QSize PhotoWidget::sizeHint() const
{
    return this->size;
}

ChatButton::ChatButton(QWidget *parent, std::shared_ptr<Chat> chat)
    :QFrame(parent), chat(chat)
{
    this->setFrameStyle(QFrame::Panel);
    this->setFrameShadow(QFrame::Raised);
    this->setLineWidth(2);
}

void ChatButton::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
}

void LabelImage::resizeLabel(QResizeEvent *event)
{
   // qDebug() << "RESIZE ";
   QLabel::resizeEvent(event);
   QRect rect(QApplication::desktop()->screenGeometry());
   if (event->size().width() < rect.width() && event->size().height() < rect.height()) {
       this->setPixmap(_qPixmap, event->size());
       this->setSize(event->size());
       // qDebug() << "photo event width " << event->size().width() << " height " << event->size().height();
   } else {
       // qDebug() << "big photo event width " << event->size().width() << " height " << event->size().height();
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
