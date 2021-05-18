#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H

#include <QToolButton>
#include <QPainter>
#include <QEvent>
#include <QPaintEvent>
#include <QObject>
#include <QLabel>
#include <QPushButton>
#include <memory>

#include "community.h"

class MyButton : public QToolButton
{
    Q_OBJECT
public:
    MyButton(const QString & text = "", QWidget *parent = nullptr);

    QSize sizeHint() const override;
};

class ChatButton :  public QFrame
{
    Q_OBJECT
signals:
    void clicked();
public:
    ChatButton(QWidget *parent = nullptr, std::shared_ptr<Chat> chat = std::make_shared<Chat>());

    void mousePressEvent(QMouseEvent *event);
    std::shared_ptr<Chat> getChat() { return chat; }
    void setChat(std::shared_ptr<Chat> chat) { this->chat = chat; }
private:
    std::shared_ptr<Chat> chat;
};

class PhotoWidget : public QLabel
{
    Q_OBJECT
public:
    PhotoWidget(QPixmap photo, QSize size = QSize(50,50), QWidget *parent = nullptr);

    QSize sizeHint() const override;
private:
    QPixmap photo;
    QSize size;
};

class LabelImage: public QLabel {

  private:
    QPixmap _qPixmap, _qPixmapScaled;

  public:
    void setPixmap(const QPixmap &qPixmap) { setPixmap(qPixmap, size()); }

  public:
    void resizeLabel(QResizeEvent * event);
    void resizeEvent(QResizeEvent * event);
    QSize getSize() { return _size; }
    void setSize(QSize newSize) { _size = newSize; }

  private:
    void setPixmap(const QPixmap &qPixmap, const QSize &size);

    QSize _size;
};


#endif // GAMEOBJECTS_H